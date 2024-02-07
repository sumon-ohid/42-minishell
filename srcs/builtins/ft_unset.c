/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:16:45 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 15:25:44 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc_envp(char **envp, int old_size, int new_size)
{
	char	**output;
	int		i;

	output = malloc(sizeof(char *) * (new_size + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		output[i] = ft_strdup(envp[i]);
		if (output[i] == NULL)
		{
			ft_putstr("ft_strdup failed at ft_realloc_envp function\n");
			return (NULL);
		}
		i++;
	}
	output[i] = NULL;
	return (output);
}

void	ft_unsetenv(t_data *node, char *str)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], str, ft_strlen(str)) == 0)
		{
			j = i;
			while (node->envp[j])
			{
				node->envp[j] = node->envp[j + 1];
				j++;
			}
			new_envp = ft_realloc_envp(node->envp, i, j);
			if (new_envp == NULL)
				return ;
			node->envp = new_envp;
		}
		i++;
	}
}

// need to do mulitple unset
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
	if (ft_strcmp(str, "unset") == 0)
	{
		ft_putstr("unset: not enough arguments\n");
		return (1);
	}
	else
	{
		while (vars[i])
			ft_unsetenv(node, vars[i++]);
	}
	free(vars);
	return (0);
}
