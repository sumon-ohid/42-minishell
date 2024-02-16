/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:03:06 by msumon            #+#    #+#             */
/*   Updated: 2024/02/16 09:03:39 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_var_exist_in_envp(t_data *node, char *var)
{
	int i;
	char *name_before_equal;
	char *var_name;
	char *new_value;

	i = 0;
	while (node->envp[i])
	{
		name_before_equal = copy_until_char(node->envp[i], '=');
		var_name = copy_until_char(var, '=');
		if (ft_strcmp(name_before_equal, var_name) == 0)
			break ;
		i++;
	}
	node->envp[i] = ft_realloc_heredoc(node->envp[i], i, i + 1);
	if (!node->envp)
		handle_error("Envp failed at ft_export function", 1);
	new_value = ft_strjoin(name_before_equal, "=", 0);
	new_value = ft_strjoin(new_value, copy_after_char(var, '='), 0);
	node->envp[i] = new_value;
	node->envp[i + 1] = NULL;
	free(name_before_equal);
	free(var_name);
	return (0);
}

int handle_var_exist_in_local_vars(t_data *node, char *var, t_vars *local_vars)
{
	int i;
	char *name_before_equal;
	char *var_name;
	char *new_value;

	i = 0;
	while (node->envp[i])
	{
		name_before_equal = copy_until_char(node->envp[i], '=');
		var_name = copy_until_char(var, '=');
		if (ft_strcmp(name_before_equal, var_name) == 0)
			break ;
		i++;
	}
	while (local_vars)
	{
		if (ft_strcmp(local_vars->first_half, var_name) == 0)
		{
			new_value = ft_strjoin(local_vars->first_half, "=", 0);
			new_value = ft_strjoin(new_value, local_vars->second_half, 0);
			node->envp[i] = ft_realloc_heredoc(node->envp[i], i, i + 1);
			node->envp[i] = new_value;
			node->envp[i + 1] = NULL;
			free(name_before_equal);
			free(var_name);
			break;
		}
		else
			local_vars = local_vars->next;
	}
	return (0);
}
