/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:27:41 by msumon            #+#    #+#             */
/*   Updated: 2024/01/26 14:43:07 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	handle_export_with_equals(t_data *node, char **var)
{
	int		i;
	char	*dup;

	i = 0;
	while (node->envp[i])
		i++;
	dup = ft_strdup(var[1]);
	if (dup == NULL)
	{
		ft_putstr("ft_strdup failed at ft_export function\n");
		return (1);
	}
	node->envp[i] = ft_realloc_heredoc(node->envp[i], i, i + 1);
    if(!node->envp)
    {
        ft_putstr("ft_realloc_envp failed at ft_export function\n");
        return (1);
    }
	node->envp[i] = dup;
    node->envp[i + 1] = NULL;
	return (0);
}

// need to fix this function
int	handle_export_without_equals(t_data *node, char **var)
{
    int		i;
    int     j;
    char	*dup;

    i = 0;
    j = 0;
    while (node->envp[i])
        i++;
    while (var[j])
    {
        dup = ft_strdup(var[j]);
        if (dup == NULL)
        {
            ft_putstr("ft_strdup failed at ft_export function\n");
            return (1);
        }   
        node->envp[i] = ft_realloc_heredoc(node->envp[i], i, i + 1);
        if(!node->envp)
        {
            ft_putstr("ft_realloc_envp failed at ft_export function\n");
            return (1);
        }
        node->envp[i] = dup;
        node->envp[i + 1] = NULL;
        j++;
    }
    return (0);
}

// need to implement if var exists do not add
int	ft_export(t_data *node, t_token *token, char *str)
{
	char	**var;

	(void)token;
	var = ft_split(str, ' ', 0, 0);
	if (var == NULL)
	{
		ft_putstr("ft_split failed at ft_export function line 26\n");
		return (1);
	}
	if (ft_strcmp(str, "export") == 0)
		return (handle_export_no_args(node));
	else if (ft_strchr(str, '=') == 1)
		return (handle_export_with_equals(node, var));
	else if (ft_strchr(str, '=') == 0)
		return (handle_export_without_equals(node, var));
	free(var);
	return (0);
}
