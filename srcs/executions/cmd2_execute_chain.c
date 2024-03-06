/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:11 by msumon            #+#    #+#             */
/*   Updated: 2024/03/06 16:19:58 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all(int ***origin, int max)
{
	int	**fd;
	int	counter;

	fd = *origin;
	counter = 0;
	while (counter < max)
	{
		if (fd[counter][0] != -1)
		{
			close(fd[counter][0]);
			fd[counter][0] = -1;
		}
		if (fd[counter][1] != -1)
		{
			close(fd[counter][1]);
			fd[counter][1] = -1;
		}
		counter++;
	}
}

int	ft_commander(t_token *chain, t_data *node)
{
	char	**environ;
	t_token	*mark;
	char	*tmp;

	environ = node->envp;
	while (chain && chain->type != COMMAND)
		chain = chain->next;
	mark = chain;
	chain = chain->next;
	while (chain && chain->type == FLAG)
	{
		tmp = ft_strjoin(mark->str, " ", 1);
		mark->str = tmp;
		if (!mark->str)
			ft_exit(node, -1, "memory allocation in commander failed");
		tmp = ft_strjoin(mark->str, chain->str, 1);
		mark->str = tmp;
		if (!mark->str)
			ft_exit(node, -1, "memory allocation in commander failed");
		chain = chain->next;
	}
	extract_find_execute(environ, mark, node);
	return (0);
}

int	execute_chain(t_data *node, t_token *chain, char *line, int processes)
{
	t_token	*proxy;

	proxy = chain;
	while (proxy)
	{
		if (proxy->type == BUILTIN)
		{
			if (processes)
				close_all(&node->fd, processes - 1);
			if (!ft_redirect_checker(chain, 0, node, 0))
				return (node->last_return = -99, -1);
			return (entry_check2(node, chain, line));
		}
		else if (proxy->type == COMMAND)
		{
			ft_redirect_checker(chain, 1, node, 0);
			return (ft_commander(chain, node));
		}
		else
			proxy = proxy->next;
	}
	return (ft_redirect_checker(chain, 0, node, 1));
}

void	set_what_this_child_doesnt_need(int ***origin, int index, int max)
{
	int	**fd;
	int	counter;

	fd = *origin;
	counter = 0;
	while (counter < index)
	{
		if (counter != index - 1)
		{
			fd[counter][1] = -1;
		}
		fd[counter][0] = -1;
		counter++;
	}
	while (counter < max)
	{
		if (counter != index)
		{
			fd[counter][0] = -1;
		}
		fd[counter][1] = -1;
		counter++;
	}
}

int	exception_checker(t_token **tokens, int processes)
{
	t_token	*proxy;

	if (processes != 1)
		return (0);
	proxy = tokens[0];
	while (proxy)
	{
		if (proxy->type == EXPORT)
			proxy->type = BUILTIN;
		if (proxy->type == BUILTIN)
			break ;
		while (proxy && proxy->type != BUILTIN)
			proxy = proxy->next;
	}
	if (!proxy)
		return (0);
	else
		return (1);
}