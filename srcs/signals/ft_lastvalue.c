/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:55:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/29 18:31:57 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lastvalue(t_data *node)
{
	if (node->last_return == -2)
		ft_putnbr(2);
	if (WIFEXITED(node->last_return))
		ft_putnbr(WEXITSTATUS(node->last_return));
	else if (WIFSIGNALED(node->last_return))
		ft_putnbr(WTERMSIG(node->last_return) + 128);
	else
		ft_putnbr(127);
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
