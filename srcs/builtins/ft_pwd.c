/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:54 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 12:50:00 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *node)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		tmp = ft_getenv("PWD",node);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("\n", 2);
		node->last_return = -99;
		return (1);
	}
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (0);
}
