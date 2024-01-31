/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:31:58 by msumon            #+#    #+#             */
/*   Updated: 2024/01/26 17:57:37 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_input(char *line)
{
	char	**tokens;

    tokens = ft_split(line, '|', 0, 0);
	if (!tokens)
	{
		write(2, "Allocation error\n", 17);
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

int	entry_check2(t_data *node, t_token *head, char *line)
{
	if (ft_strcmp(head->str, "cd") == 0)
		if (head->next)
			ft_cd(head->next->str, node);
		else
			ft_cd(NULL, node);
	else if (ft_strcmp(head->str, "echo") == 0)
		ft_echo(line, node);
	else if (ft_strcmp(head->str, "env") == 0)
		ft_env(node);
	else if (ft_strcmp(head->str, "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(head->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(head->str, "exit") == 0)
		exit(0);
	else if (ft_strstr(head->str, "export") != 0)
		ft_export(node, head, line);
	else if (ft_strcmp(head->str, "unset") == 0)
		ft_unset(node, head, line);
	else
		printf("minishell: %s: command not found\n", line);
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

void	fork_processes(int processes, t_data *node, t_token **tokens,
		char *line)
{
	int	counter;

	counter = 0;
	while (counter < processes)
	{
		node->pid[counter] = fork();
		if (node->pid[counter] == 0)
		{
			if (counter != 0)
				dup2(node->fd[counter - 1][0], STDIN_FILENO);
			if (counter != processes - 1)
				dup2(node->fd[counter][1], STDOUT_FILENO);
			close_what_this_child_doesnt_need(&node->fd, counter, processes
				- 1);
			execute_chain(node, tokens[counter], line, processes);
			exit(1);
		}
		else if (node->pid[counter] == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		counter++;
	}
}
