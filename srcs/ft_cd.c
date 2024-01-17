/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 09:24:44 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *str)
{
	if (str)
	{
		if (chdir(str) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr("\n");
		}
	}
	else
		chdir("/Users/new_dir");
}
