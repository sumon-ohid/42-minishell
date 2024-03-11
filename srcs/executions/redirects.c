/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/11 13:17:25 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set(t_data *node)
{
	node->local_vars = NULL;
	node->std_in = dup(STDIN_FILENO);
	if (node->std_in == -1)
		ft_exit(node, -1, "dup failed");
	node->std_out = dup(STDOUT_FILENO);
	if (node->std_out == -1)
		ft_exit(node, -1, "dup failed");
	node->old_turn = 0;
	node->oldpwd = getenv("OLDPWD");
	node->pwd = getenv("PWD");
}

void	ft_restore(t_data *node)
{
	if (dup2(node->std_in, STDIN_FILENO) == -1)
		ft_exit(node, -1, "dup2 failed");
	if (dup2(node->std_out, STDOUT_FILENO) == -1)
		ft_exit(node, -1, "dup2 failed");
}

int	ft_redirect_checker(t_token *proxy, int mode, t_data *node, int killmode)
{
	t_token	*mark;

	mark = NULL;
	while (proxy)
	{
		if (proxy->type >= 3 && proxy->type <= 5)
		{
			if (!ft_redirector(proxy->next, proxy->type + 3, mode, node))
			{
				if (killmode)
					ft_exit(node, 1, NULL);
				else
					return (0);
			}
			if (proxy->type == INFILE)
				mark = NULL;
		}
		else if (proxy->type == HEREDOC)
			mark = proxy;
		proxy = proxy->next;
	}
	if (mark)
		read_from_heredoc(mark, node);
	return (1);
}
