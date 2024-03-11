/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:27:41 by msumon            #+#    #+#             */
/*   Updated: 2024/03/11 18:02:19 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	sort_env(char **arr, int n)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	while (i < n)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && ft_strncmp(arr[j], key, 1) > 0)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

int	handle_export_no_args(t_data *node)
{
	int		i;
	char	*var_value;
	char	*var_name;
	char	*tmp;

	sort_env(node->envp, ft_strlen_arr(node->envp));
	i = 0;
	while (node->envp[i])
	{
		var_name = copy_until_char(node->envp[i], '=');
		if (!var_name)
			ft_exit(node, -1, "malloc failed at ft_export function");
		tmp = copy_after_char(node->envp[i], '=');
		if (!tmp)
			ft_exit(node, -1, "malloc failed at ft_export function");
		var_value = remove_quote(tmp);
		printf("declare -x %s=\"%s\"\n", var_name, var_value);
		free(var_name);
		free(tmp);
		free(var_value);
		i++;
	}
	return (0);
}

int	check_if_var_exists(t_data *node, char *var)
{
	int		i;
	char	*name_before_equal;
	char	*var_name;

	i = 0;
	var_name = copy_until_char(var, '=');
	if (!var_name)
		ft_exit(node, -1, "malloc failed at ft_export function");
	while (node->envp[i])
	{
		name_before_equal = copy_until_char(node->envp[i], '=');
		if (!name_before_equal)
			ft_exit(node, -1, "malloc failed at ft_export function");
		if (ft_strcmp(name_before_equal, var_name) == 0)
		{
			free(name_before_equal);
			free(var_name);
			return (1);
		}
		free(name_before_equal);
		i++;
	}
	free(var_name);
	return (0);
}

int	handle_export(t_data *node, char **var)
{
	int	var_exists;
	int	i;

	i = 1;
	while (var[i])
	{
		var_exists = check_if_var_exists(node, var[i]);
		if (var_name_check(var[i]) == 1)
		{
			printf("minishell: export: `%s': not a valid identifier\n", var[i]);
			node->last_return = -99;
		}
		else
		{
			if (var_exists == NOT_EXIST)
				handle_var_not_exists(node, var[i]);
			else if (var_exists == EXIST_ENVP)
				handle_var_exist_in_envp(node, var[i]);
		}
		i++;
	}
	free_arr(var);
	return (0);
}

int	ft_export(t_data *node, t_token *token, char *str)
{
	char	**var;

	(void)token;
	var = ft_split_special(str, ' ', 'P', 0);
	if (var == NULL)
		ft_exit(node, 1, "Malloc failed at ft_export function");
	if (ft_strcmp(var[0], "export") == 0 && var[1] == NULL)
	{
		handle_export_no_args(node);
		free_arr(var);
		return (0);
	}
	else
	{
		handle_export(node, var);
		return (0);
	}
	return (1);
}
