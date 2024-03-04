/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/03/04 20:21:49 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	wait_for_processes(int *pid, int *status, int processes, t_data *node)
{
	int	counter;

	(void)node;
	counter = 0;
	while (counter < processes)
	{
		waitpid(pid[counter], &status[counter], 0);
		counter++;
	}
}*/

void	wait_for_processes(int *pid, int *status, int processes, t_data *node)
{
	int	counter;
	int	return_val;

	counter = 0;
	while (counter < processes)
	{
		return_val = waitpid(pid[counter], &status[counter], WNOHANG);
		if (return_val == -1)
			ft_exit(node, 127, "error in execution part");
		else if (return_val == 0)
		{
			if (g_signal == CTRL_C)
			{
				kill(pid[counter], SIGINT);
				g_signal = 0;
			}
		}
		else
		{
			if (WIFSIGNALED(status[counter]) && WTERMSIG(status[counter]) == 3)
				printf("Quit (core dumped)\n");
			else if (WIFSIGNALED(status[counter]) && counter == processes - 1
				&& node->mode != HEREDOC)
				write(STDOUT_FILENO, "\n", 1);
			if (WIFEXITED(status[counter]) || WIFSIGNALED(status[counter]))
				counter++;
		}
	}
}


void	free_resources(int **fd, int processes, t_data *node)
{
	int	counter;

	counter = 0;
	free(node->pid);
	node->pid = NULL;
	free(node->status);
	node->status = NULL;
	while (counter < processes - 1)
	{
		free(fd[counter]);
		counter++;
	}
	free(fd);
}

void	do_child_stuff(char *line, t_data *node, int i, t_token **tokens)
{
	mode(node, CHILD);
	//if (pipe_counter(line) - 1 != i)
		//close(node->fd[i][0]);
	if (i != 0)
	{
		if (dup2(node->fd[i - 1][0], STDIN_FILENO) == -1)
			exit_builtin(node);
		close(node->fd[i - 1][0]);
	}
	if (i != node->processes - 1)
	{
		if (dup2(node->fd[i][1], STDOUT_FILENO) == -1)
			exit_builtin(node);
		close(node->fd[i][1]);
		close(node->fd[i][0]); //THE SIGPIPE CLOSE
	}
	//set_what_this_child_doesnt_need(&node->fd, i, node->processes - 1);
	node->cur_proc = i;
	node->in_child = 1;
	execute_chain(node, tokens[i], line, node->processes);
	exit_builtin(node);
}

void	fork_processes(int processes, t_data *node, t_token **tokens,
		char *line)
{
	int	i;

	i = 0;
	while (i < processes)
	{
		if (i < processes - 1)
			if (pipe(node->fd[i]) == -1)
				ft_exit(node, -1, "pipe creation failed");
		node->pid[i] = fork();
		if (node->pid[i] == 0)
			do_child_stuff(line, node, i, tokens);
		else if (node->pid[i] == -1)
			ft_exit(node, -1, "forking failed");
		else
			parent_close(node, i, processes);
		i++;
	}
	if (processes > 1)
		close(node->fd[processes - 2][0]);
}
//this i removed from child execution:
/* if (i != 0)
	dup2(node->fd[i - 1][0], STDIN_FILENO); //protect these & close some stuff
if (i != processes - 1)
	dup2(node->fd[i][1], STDOUT_FILENO);
close_what_this_child_doesnt_need(&node->fd, i, processes - 1);
node->cur_proc = i;
node->in_child = 1;
execute_chain(node, tokens[i], line, processes);
exit_builtin(node);*/


int	executor_init(t_data *node, t_token **tokens, int processes, char *line)
{
	//int	pid[512];
	//int	status[512];
	int	**fd;
	int	lastval;

	fd = NULL;
	node->processes = processes;
	allocate_fd(&fd, processes, node);
	node->fd = fd;
	if (exception_checker(tokens, processes))
	{
		execute_chain(node, tokens[0], line, 0);
		return (0);
	}
	node->pid = malloc(sizeof(int) * processes);
	node->status = malloc(sizeof(int) * processes);
	fork_processes(processes, node, tokens, line);
	close_all(&fd, processes - 1);
	wait_for_processes(node->pid, node->status, processes, node);
	lastval = node->status[processes - 1];
	free_resources(fd, processes, node);
	return (lastval);
}
