/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:16:45 by msumon            #+#    #+#             */
/*   Updated: 2024/02/20 14:59:43 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unsetenv(t_data *node, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], str, ft_strlen(str)) == 0)
		{
			j = i;
			free(node->envp[i]);
			while (node->envp[j])
			{
				node->envp[j] = node->envp[j + 1];
				j++;
			}
			node->envp[j] = NULL;
		}
		else
			i++;
	}
}

int	ft_unset(t_data *node, t_token *token, char *str)
{
	int		i;
	char	**vars;

	(void)token;
	vars = ft_split(str, ' ', 0, 0);
	if (vars == NULL)
	{
		ft_putstr("ft_split failed at ft_unset function\n");
		return (1);
	}
	i = 1;
	while (vars[i])
	{
		ft_unsetenv(node, vars[i]);
		i++;
	}
	free_arr(vars);
	return (0);
}
