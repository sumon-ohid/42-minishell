/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:31:58 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 19:27:57 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_cd(t_data *node, t_token *head)
{
	if (head->next && !head->next->next)
		return (ft_cd(head->next->str, node));
	else if (!head->next)
		return (ft_cd(NULL, node));
	else if (head->next->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (-1);
	}
	return (0);
}

int	entry_check2(t_data *node, t_token *head, char *line)
{
	if (ft_strcmp(head->str, "cd") == 0)
		return (prepare_cd(node, head));
	else if (ft_strcmp(head->str, "echo") == 0)
		ft_echo(line, node, head);
	else if (ft_strcmp(head->str, "env") == 0)
		ft_env(node);
	else if (ft_strcmp(head->str, "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(head->str, "pwd") == 0)
		ft_pwd(node);
	else if (ft_strcmp(head->str, "exit") == 0 && node->in_child == 0)
		return (exit_with_args(node, ft_lastvalue(node), head, 0));
	else if (ft_strcmp(head->str, "export") == 0)
		ft_export(node, head, line);
	else if (ft_strcmp(head->str, "unset") == 0)
		ft_unset(node, head, line);
	else if (ft_strcmp(head->str, "exit") != 0)
		nocomm_error(head->str);
	ft_restore(node);
	return (0);
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
		counter++;
	}
}

void	exit_builtin(t_data *node)
{
	close(node->std_in);
	close(node->std_out);
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
