/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/01/17 09:24:36 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 14:11:22 by sumon            ###   ########.fr       */
=======
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/01/17 19:32:25 by msumon           ###   ########.fr       */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *str)
{
	if (str)
	{
		if (chdir(str) == -1)
		{
			ft_putstr("cd: no such directory: ");
			ft_putstr("\n");
		}
	}
}
