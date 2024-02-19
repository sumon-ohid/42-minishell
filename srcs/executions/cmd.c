/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/02/19 11:24:05 by msumon           ###   ########.fr       */
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
				kill(pid[counter], SIGABRT);
				g_signal = 0;
			}
		}
		else
		{
			if (WIFEXITED(status[counter]) || WIFSIGNALED(status[counter]))
				counter++;
		}
	}
}

void	free_resources(int **fd, int processes)
{
	int	counter;

	counter = 0;
	while (counter < processes - 1)
	{
		free(fd[counter]);
		counter++;
	}
	free(fd);
}

int	executor_init(t_data *node, t_token **tokens, int processes, char *line)
{
	int	pid[512];
	int	status[512];
	int	**fd;

	fd = NULL;
	node->pid = pid;
	node->processes = processes;
	if (exception_checker(tokens, processes))
	{
		execute_chain(node, tokens[0], line, 0);
		return (0);
	}
	allocate_fd(&fd, processes);
	node->fd = fd;
	fork_processes(processes, node, tokens, line);
	close_all(&fd, processes - 1);
	wait_for_processes(pid, status, processes, node);
	free_resources(fd, processes);
	return (status[processes - 1]);
}
