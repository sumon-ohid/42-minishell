/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:24 by msumon            #+#    #+#             */
/*   Updated: 2024/03/07 14:39:34 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_var(char *envp)
{
	char *new_envp;
	
	new_envp = remove_quote(envp);
	printf("%s\n", new_envp);
	free(new_envp);
}

char	**ft_env(t_data *node)
{
	int		i;
	char	**envp;

	i = 0;
	envp = node->envp;
	while (envp[i])
	{
		print_env_var(envp[i]);
		i++;
	}
	return (envp);
}
