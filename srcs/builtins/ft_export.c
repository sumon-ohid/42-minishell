/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:27:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/22 16:21:20 by msumon           ###   ########.fr       */
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

int	check_if_var_exists(t_data *node, char *var)
{
    int		i;
    char	*name_before_equal;
    char	*var_name;

    i = 0;
	var_name = copy_until_char(var, '=');
    while (node->envp[i])
    {
        name_before_equal = copy_until_char(node->envp[i], '=');
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
		if (var_exists == NOT_EXIST)
			handle_var_not_exists(node, var[i]);
		else if (var_exists == EXIST_ENVP)
			handle_var_exist_in_envp(node, var[i]);
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
