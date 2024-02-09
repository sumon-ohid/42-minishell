/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:31:58 by msumon            #+#    #+#             */
/*   Updated: 2024/02/09 16:39:15 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	entry_check2(t_data *node, t_token *head, char *line)
{
	if (ft_strcmp(head->str, "cd") == 0)
	{
		if (head->next)
			ft_cd(head->next->str, node);
		else
			ft_cd(NULL, node);
	}
	else if (ft_strcmp(head->str, "echo") == 0)
		ft_echo(line, node, head);
	else if (ft_strcmp(head->str, "env") == 0)
		ft_env(node);
	else if (ft_strcmp(head->str, "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(head->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(head->str, "exit") == 0)
		ft_exit(node, 0, NULL);
	else if (ft_strstr(head->str, "export") != 0)
		ft_export(node, head, line);
	else if (ft_strcmp(head->str, "unset") == 0)
		ft_unset(node, head, line);
	else
		printf("minishell: %s: command not found\n", line);
	ft_restore(node);
	return (1);
}

void	allocate_fd(int ***fd, int processes)
{
	int	counter;

	counter = 0;
	*fd = malloc(sizeof(int *) * (processes - 1));
	if (!*fd)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while (counter < processes - 1)
	{
		(*fd)[counter] = malloc(sizeof(int) * 2);
		if (!(*fd)[counter])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		if (pipe((*fd)[counter]) == -1)
		{
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
		counter++;
	}
}

void	parent_close(t_data *node, int i, int processes)
{
	if (i != 0)
		close(node->fd[i - 1][0]);
	if (i != processes - 1)
		close(node->fd[i][1]);
}

void	fork_processes(int processes, t_data *node, t_token **tokens,
		char *line)
{
	int	i;

	i = 0;
	while (i < processes)
	{
		node->pid[i] = fork();
		if (node->pid[i] == 0)
		{
			if (i != 0)
				dup2(node->fd[i - 1][0], STDIN_FILENO);
			if (i != processes - 1)
				dup2(node->fd[i][1], STDOUT_FILENO);
			close_what_this_child_doesnt_need(&node->fd, i, processes - 1);
			node->cur_proc = i;
			execute_chain(node, tokens[i], line, processes);
			exit(1);
		}
		else if (node->pid[i] == -1)
			handle_error("Fork failed", 1);
		else
			parent_close(node, i, processes);
		i++;
	}
	if (processes > 1)
		close(node->fd[processes - 2][0]);
}
