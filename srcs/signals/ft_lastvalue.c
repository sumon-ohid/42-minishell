/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:55:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/02 19:58:59 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lastvalue(t_data *node)
{
	if (node->last_return == -2)
		return(2);
	else if (node->last_return == -1)
		return (1);
	else if (node->last_return == -88)
		return (130);
	if (WIFEXITED(node->last_return))
		return(WEXITSTATUS(node->last_return));
	else if (WIFSIGNALED(node->last_return))
		return(WTERMSIG(node->last_return) + 128);
	else
		return(127);
}

char	*ft_lastval_str(t_data *node)
{
	char	*result;

	if (node->last_return == -2)
		result = ft_itoa(2);
	else if (node->last_return == -1)
		result = ft_itoa(1);
	else if (WIFEXITED(node->last_return))
		result = ft_itoa(WEXITSTATUS(node->last_return));
	else if (WIFSIGNALED(node->last_return))
		result = ft_itoa(WTERMSIG(node->last_return) + 128);
	else
		result = ft_itoa(127);
	if (!result)
		ft_exit(node, -1, "malloc in itoa failed");
	return (result);
}
