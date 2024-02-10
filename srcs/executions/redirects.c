/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/10 12:56:29 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set(t_data *node)
{
	node->local_vars = NULL;
	node->std_in = dup(STDIN_FILENO);
	if (node->std_in == -1)
		exit(-1);
	node->std_out = dup(STDOUT_FILENO);
	if (node->std_out == -1)
		exit(-1);
}

void	ft_restore(t_data *node)
{
	if (dup2(node->std_in, STDIN_FILENO) == -1)
		exit(-1);
	close(node->std_in);
	if (dup2(node->std_out, STDOUT_FILENO) == -1)
	close(node->std_in);
		exit(-1);
}

int	ft_redirect_checker(t_token *chain, int mode)
{
	t_token	*proxy;

	proxy = chain;
	while (proxy)
	{
		if (proxy->type >= 3 && proxy->type <= 5)
		{
			if (!ft_redirector(chain, proxy->type + 3, mode))
				return (0);
		}
		else if (proxy->type == HEREDOC)
		{
			read_from_heredoc(proxy);
		}
		proxy = proxy->next;
	}
	return (1);
}
