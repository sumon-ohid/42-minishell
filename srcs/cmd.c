/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/26 18:30:32 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_for_processes(int *pid, int *status, int processes)
{
	int	counter;

	counter = 0;
	while (counter < processes)
	{
		waitpid(pid[counter], &status[counter], 0);
		counter++;
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
	//free(status);
}

int	executor_init(t_data *node, t_token **tokens, int processes, char *line)
{
	int	pid[512];
	int	*status;
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
	status = malloc(sizeof(int) * processes);
	if (!status)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	wait_for_processes(pid, status, processes);
	free_resources(fd, processes);
	return (status[processes - 1]);
}
