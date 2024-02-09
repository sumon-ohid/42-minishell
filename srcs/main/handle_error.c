/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:37:29 by msumon            #+#    #+#             */
/*   Updated: 2024/02/09 20:17:20 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(char *error, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit (status);
}

void	nocomm_error(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
}
