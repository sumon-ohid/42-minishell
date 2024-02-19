/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:27:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/19 16:24:08 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

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

int	check_if_var_exists(t_data *node, char *var, t_vars *local_vars)
{
	int		i;
	char	*name_before_equal;
	char	*var_name;

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

int	handle_var_not_exists(t_data *node, char *var)
{
	int	i;

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

int	handle_export(t_data *node, char **var, t_vars *local_vars)
{
	int	var_exists;
	int	i;

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
	free_arr(var);
	return (0);
}

int	ft_export(t_data *node, t_token *token, char *str)
{
	char	**var;
	t_vars	*local_vars;

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
	return (0);
}
