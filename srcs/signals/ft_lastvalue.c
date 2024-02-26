/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:55:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/26 13:17:57 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lastvalue(t_data *node)
{
	if (WIFEXITED(node->last_return))
		ft_putnbr(WEXITSTATUS(node->last_return));
	else
		ft_putnbr(127);
}

char	*ft_lastval_str(t_data *node)
{
	char	*result;

	if (node->last_return == 2)
		result = ft_itoa(2);
	else if (WIFEXITED(node->last_return))
		result = ft_itoa(WEXITSTATUS(node->last_return));
	else
		result = ft_itoa(127);
	if (!result)
		ft_exit(node, -1, "malloc in itoa failed");
	return (result);
}
