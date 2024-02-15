/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:27:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/15 18:56:03 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NOT_EXIST 0
#define EXIST_ENVP 1
#define EXIST_LOCAL_VARS 2

int	handle_export_no_args(t_data *node)
{
	int	i;

	i = 0;
	while (node->envp[i])
	{
		printf("declare -x %s\n", node->envp[i]);
		i++;
	}
	return (0);
}

int check_if_var_exists(t_data *node, char *var, t_vars *local_vars)
{
	int i;
	char *name_before_equal;
	char *var_name;

	i = 0;
	while (node->envp[i])
	{
		name_before_equal = copy_until_char(node->envp[i], '=');
		var_name = copy_until_char(var, '=');
		if (ft_strcmp(name_before_equal, var_name) == 0)
			return (1);
		i++;
	}
	while (local_vars)
	{
		var_name = copy_until_char(var, '=');
		if (ft_strcmp(local_vars->first_half, var_name) == 0)
			return (2);
		local_vars = local_vars->next;
	}
	return (0);
}

int handle_var_not_exists(t_data *node, char *var)
{
	int i;

	i = 0;
	while (node->envp[i])
		i++;
    node->envp[i] = ft_realloc_heredoc(node->envp[i], i, i + 1);
    if (!node->envp)
        handle_error("Envp failed at ft_export function", 1);
    node->envp[i] = ft_strdup(var);
    node->envp[i + 1] = NULL;
	return (0);
}

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
	new_value = ft_strjoin(new_value, copy_after_char(var, '='), 1);
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
			new_value = ft_strjoin(new_value, local_vars->second_half, 1);
			node->envp[i] = new_value;
			node->envp[i + 1] = NULL;
			free(name_before_equal);
			free(var_name);
			break;
		}
		local_vars = local_vars->next;
	}
	return (0);
}

int handle_export(t_data *node, char **var, t_vars *local_vars)
{
	int var_exists;
	int i;

	i = 1;
	while (var[i])
	{
		var_exists = check_if_var_exists(node, var[i], local_vars);
		if (var_exists == NOT_EXIST)
			handle_var_not_exists(node, var[i]);
		else if (var_exists == EXIST_ENVP)
			handle_var_exist_in_envp(node, var[i]);
		else if (var_exists == EXIST_LOCAL_VARS)
			handle_var_exist_in_local_vars(node, var[i], local_vars);
		i++;
	}
	return (0);
}

int	ft_export(t_data *node, t_token *token, char *str)
{
	char	**var;
	t_vars *local_vars;

	local_vars = node->local_vars;
	(void)token;
	var = ft_split(str, ' ', 0, 0);
	if (var == NULL)
	{
		ft_putstr("ft_split failed at ft_export function\n");
		return (1);
	}
	if (ft_strcmp(var[0], "export") == 0 && var[1] == NULL) 
		return (handle_export_no_args(node));
	else
		return (handle_export(node, var, local_vars));
	free_arr(var);
	return (0);
}
