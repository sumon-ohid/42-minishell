/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:32:22 by msumon            #+#    #+#             */
/*   Updated: 2024/03/14 20:49:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_argument(char *arg, t_data *node)
{
	int	i;

	i = 0;
	(void)node;
	if (ft_strcmp(arg, "\"\'\"") == 0)
	{
		ft_putstr("\'");
		return ;
	}
	if (ft_strcmp(arg, "\'\"\'") == 0)
	{
		ft_putstr("\"");
		return ;
	}
	while (arg[i])
	{
		ft_putchar(arg[i]);
		i++;
	}
	return ;
}

char	*copy_after_char(char *str, char c)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	if (ft_strchr(str, c) == 0)
		return (ft_strdup(""));
	while (str[i] != c)
		i++;
	i++;
	output = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	if (!output)
		return (NULL);
	while (str[i])
	{
		output[j] = str[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}

int	remove_only_spaces(char *envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i])
		return (1);
	i++;
	while (envp[i] && envp[i] == ' ')
		i++;
	if (!envp[i])
		return (1);
	else
		return (0);
}

char	*get_env_value(char *arg, t_data *node, int i)
{
	char	*env_value;
	char	*tmp;

	while (node->envp[i])
	{
		if (remove_only_spaces(node->envp[i]))
			return ("");
		tmp = copy_until_char(node->envp[i], '=');
		if (!tmp)
			ft_exit(node, 127, "malloc error in get_env");
		if (ft_strcmp(tmp, arg) == 0)
		{
			if (node->envp[i][ft_strlen(tmp)] == '=')
				env_value = node->envp[i] + ft_strlen(tmp) + 1;
			else if (node->envp[i][ft_strlen(tmp)] == '\0')
				env_value = "";
			else
				env_value = arg;
			return (free(tmp), env_value);
		}
		free(tmp);
		i++;
	}
	return ("");
}
