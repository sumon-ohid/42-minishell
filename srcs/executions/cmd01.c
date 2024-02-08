/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:11 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 15:24:34 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_commander(t_token *chain)
{
	extern char	**environ;
	t_token		*mark;
	char		*tmp;

	while (chain && chain->type != COMMAND)
		chain = chain->next;
	mark = chain;
	chain = chain->next;
	while (chain && chain->type == FLAG)
	{
		tmp = ft_strjoin(mark->str, " ", 1);
		mark->str = tmp;
		tmp = ft_strjoin(mark->str, chain->str, 1);
		mark->str = tmp;
		if (!mark->str)
		{
			perror("Memory allocation failed");
			exit(-1);
		}
		chain = chain->next;
	}
	extract_find_execute(environ, mark->str);
	return (0);
}

void	close_all(int ***origin, int max)
{
	int	**fd;
	int	counter;

	fd = *origin;
	counter = 0;
	while (counter < max)
	{
		close(fd[counter][0]);
		close(fd[counter][1]);
		counter++;
	}
}

int	execute_chain(t_data *node, t_token *chain, char *line, int processes)
{
	t_token	*proxy;

	proxy = chain;
	if (!chain)
		return (-1);
	ft_redirect_checker(chain);
	while (proxy)
	{
		if (proxy->type == BUILTIN)
		{
			if (processes)
				close_all(&node->fd, processes - 1);
			return (entry_check2(node, chain, line));
		}
		else if (proxy->type == COMMAND)
			return (ft_commander(chain));
		else
			proxy = proxy->next;
	}
	return (0);
}

void	close_what_this_child_doesnt_need(int ***origin, int index, int max)
{
	int	**fd;
	int	counter;

	fd = *origin;
	counter = 0;
	while (counter < index)
	{
		if (counter != index - 1)
		{
			close(fd[counter][1]);
		}
		close(fd[counter][0]);
		counter++;
	}
	while (counter < max)
	{
		if (counter != index)
		{
			close(fd[counter][0]);
		}
		close(fd[counter][1]);
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