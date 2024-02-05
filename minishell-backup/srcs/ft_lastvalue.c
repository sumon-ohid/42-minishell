/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:55:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/05 17:55:35 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_lastvalue(t_data *node)
{
    if (WIFEXITED(node->last_return))
        ft_putnbr(WEXITSTATUS(node->last_return));
    else
        ft_putnbr(127); //for now
}

char    *ft_lastval_str(t_data *node)
{
    char *result;

    if (WIFEXITED(node->last_return))
        result = ft_itoa(WEXITSTATUS(node->last_return));
    else
        result = ft_itoa(127); //for now
    if (!result)
        exit(EXIT_FAILURE);
    return (result);
}
