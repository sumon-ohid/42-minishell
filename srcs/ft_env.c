/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:24 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 09:52:40 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_env(void)
{
	extern char	**environ;
	int			i;
	char		**envp;
	char		**envp2;

	envp = environ;
	i = 0;
	while (envp[i])
		i++;
	envp2 = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		envp2[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		printf("%s\n", envp[i]);
		i++;
	}
	return (envp2);
}
