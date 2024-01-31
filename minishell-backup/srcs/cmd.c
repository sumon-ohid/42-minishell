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

void	free_resources(int **fd, int *status, int processes)
{
	int	counter;

	counter = 0;
	while (counter < processes - 1)
	{
		free(fd[counter]);
		counter++;
	}
	free(fd);
	free(status);
}

void	executor_init(t_data *node, t_token **tokens, int processes, char *line)
{
	int	pid[512];
	int	*status;
	int	**fd;

	fd = NULL;
	node->fd = fd;
	node->pid = pid;
	node->processes = processes;
	if (exception_checker(tokens, processes))
	{
		execute_chain(node, tokens[0], line);
		return ;
	}
	allocate_fd(&fd, processes);
	node->fd = fd;
	fork_processes(processes, node, tokens, line);
	status = malloc(sizeof(int) * processes);
	if (!status)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	wait_for_processes(pid, status, processes);
	free_resources(fd, status, processes);
}

int	entry_check(t_data *node, char *line)
{
	char	**arr;
	t_token	**tokens;

	tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	if (!tokens)
	{
		perror("Memory allocation failed");
		return (1);
	}
	arr = parse_input(line);
	if (!arr)
	{
		free(tokens);
		return (1);
	}
	process_words(&tokens, arr, line);
	executor_init(node, tokens, pipe_counter(line), line);
	//free_tokens(tokens);
	free(line);
	free_arr(arr);
	return (0);
}
