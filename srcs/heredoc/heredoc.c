/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:40:57 by msumon            #+#    #+#             */
/*   Updated: 2024/02/21 11:27:14 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_counter(t_token *tokens)
{
	t_token	*proxy;
	int		counter;

	proxy = tokens;
	counter = 0;
	while (proxy)
	{
		if (proxy->type == HEREDOC)
			counter++;
		proxy = proxy->next;
	}
	return (counter);
}

int	check_for_heredoc(t_data *node, t_token **tokens, int processes)
{
	t_token	*proxy;
	int		counter;

	counter = 0;
	while (counter < processes)
	{
		proxy = tokens[counter];
		while (proxy)
		{
			if (proxy->type == HEREDOC && proxy->next)
			{
				proxy->heredoc_data = ft_heredoc(node, proxy->next->str);
				if (!proxy->heredoc_data)
					return (0);
			}
			proxy = proxy->next;
		}
		counter++;
	}
	return (1);
}

// cat << eof > out | << rr give syntax error but in bash its valid
// protect pipe??

void	read_from_heredoc(t_token *heredoc)
{
	int	tomlo[2];

	pipe(tomlo);
	dup2(tomlo[0], STDIN_FILENO);
	close(tomlo[0]);
	write(tomlo[1], heredoc->heredoc_data, ft_strlen(heredoc->heredoc_data));
	close(tomlo[1]);
	free(heredoc->heredoc_data);
}
