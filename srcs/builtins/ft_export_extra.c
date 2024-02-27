/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:03:06 by msumon            #+#    #+#             */
/*   Updated: 2024/02/27 09:51:47 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	handle_var_exist_in_envp(t_data *node, char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = copy_until_char(var, '=');
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], var_name, ft_strlen(var_name)) == 0
			&& node->envp[i][ft_strlen(var_name)] == '=')
		{
			free(var_name);
			free(node->envp[i]);
			node->envp[i] = ft_strdup(var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	handle_var_not_exists(t_data *node, char *var)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen_arr(node->envp) + 2));
	if (!new_envp)
		ft_exit(node, -1, "malloc failed at ft_export function");
	while (node->envp[i])
	{
		new_envp[i] = ft_strdup(node->envp[i]);
		if (!new_envp[i])
			ft_exit(node, -1, "malloc failed at ft_export function");
		i++;
	}
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
		ft_exit(node, -1, "malloc failed at ft_export function");
	new_envp[i + 1] = NULL;
	free_arr(node->envp);
	node->envp = new_envp;
	return (0);
}
