/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:31:58 by msumon            #+#    #+#             */
/*   Updated: 2024/02/22 12:31:44 by codespace        ###   ########.fr       */
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
	else if (ft_strstr(head->str, "unset") != 0)
		ft_unset(node, head, line);
	else
		nocomm_error(head->str);
	ft_restore(node);
	return (1);
}

void	allocate_fd(int ***fd, int processes, t_data *node)
{
	int	counter;

	counter = 0;
	if (processes - 1)
		*fd = malloc(sizeof(int *) * (processes - 1));
	if (!*fd && processes - 1)
		ft_exit(node, -1, "memory allocation failed");
	while (counter < processes - 1)
	{
		(*fd)[counter] = malloc(sizeof(int) * 2);
		if (!(*fd)[counter])
		{
			free(*fd);
			ft_exit(node, -1, "memory allocation failed");
		}
		if (pipe((*fd)[counter]) == -1)
		{
			//ft_free_array(*fd);
			ft_exit(node, -1, "pipe creation failed");
		}
		counter++;
	}
}

void	exit_builtin(t_data *node)
{
	//char *argv[] = {"/bin/true", NULL};

	//execve("/bin/true", argv, NULL);
	ft_free_fds(node);
	ft_exit(node, 0, NULL);
}

void	parent_close(t_data *node, int i, int processes)
{
	if (i != 0)
		close(node->fd[i - 1][0]);
	if (i != processes - 1)
		close(node->fd[i][1]);
}

