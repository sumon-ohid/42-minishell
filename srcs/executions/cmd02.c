/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:31:58 by msumon            #+#    #+#             */
/*   Updated: 2024/03/04 19:23:28 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	entry_check2(t_data *node, t_token *head, char *line)
{
	if (ft_strcmp(head->str, "cd") == 0)
	{
		if (head->next)
			return (ft_cd(head->next->str, node));
		else
			return (ft_cd(NULL, node));
	}
	else if (ft_strcmp(head->str, "echo") == 0)
		ft_echo(line, node, head);
	else if (ft_strcmp(head->str, "env") == 0)
		ft_env(node);
	else if (ft_strcmp(head->str, "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(head->str, "pwd") == 0)
		ft_pwd(node);
	else if (ft_strcmp(head->str, "exit") == 0 && node->in_child == 0)
		exit_with_args(node, ft_lastvalue(node), head);
	else if (ft_strstr(head->str, "export") != 0)
		ft_export(node, head, line);
	else if (ft_strstr(head->str, "unset") != 0)
		ft_unset(node, head, line);
	else if (ft_strcmp(head->str, "exit") != 0)
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
		(*fd)[counter][0] = -1;
		(*fd)[counter][1] = -1;
		/*if (pipe((*fd)[counter]) == -1)
		{
			//free fds here
			ft_exit(node, -1, "pipe creation failed");
		}*/
		counter++;
	}
}

void	exit_builtin(t_data *node)
{
	ft_free_fds(node);
	if (node->last_return == -99)
		ft_exit(node, 1, NULL);
	else
		ft_exit(node, 0, NULL);
}

void	parent_close(t_data *node, int i, int processes)
{
	if (i != 0)
		close(node->fd[i - 1][0]);
	if (i != processes - 1)
		close(node->fd[i][1]);
}
