/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:16:45 by msumon            #+#    #+#             */
/*   Updated: 2024/01/24 20:37:47 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unsetenv(t_data *node, char *name)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen(name) + 1));
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], name, ft_strlen(name)) != 0)
		{
			new_envp[j] = malloc(sizeof(char) * (ft_strlen(node->envp[i]) + 1));
			new_envp[j] = ft_strcpy(new_envp[j], node->envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	node->envp = new_envp;
}
