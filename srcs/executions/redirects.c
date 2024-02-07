/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/07 15:40:03 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set(t_data *node)
{
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
	if (dup2(node->std_out, STDOUT_FILENO) == -1)
		exit(-1);
}

void	ft_redirect_checker(t_token *chain)
{
	t_token	*proxy;

	proxy = chain;
	while (proxy)
	{
		if (proxy->type >= 3 && proxy->type <= 5)
		{
			ft_redirector(chain, proxy->type + 3);
		}
		else if (proxy->type == HEREDOC)
		{
			read_from_heredoc(proxy);
		}
		proxy = proxy->next;
	}
}
