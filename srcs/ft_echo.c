/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by msumon            #+#    #+#             */
/*   Updated: 2024/01/17 19:15:32 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *arg)
{
	char	*env_name;
	char	*env_value;
	char	*env_value2;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	env_name = ft_strndup(arg + 1, i - 1);
	env_value = getenv(env_name);
	if (env_value)
	{
		env_value2 = malloc(sizeof(char) * (ft_strlen(env_value) + 1));
		while (env_value[j])
		{
			env_value2[j] = env_value[j];
			j++;
		}
		env_value2[j] = '\0';
		free(env_name);
		return (env_value2);
	}
	return (free(env_name), "");
}

void	print_argument(char *arg)
{
	char	*inside_quotes;

	if ((arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"') || (arg[0] == '\''
			&& arg[ft_strlen(arg) - 1] == '\''))
	{
		inside_quotes = ft_strndup(arg + 1, ft_strlen(arg) - 2);
		ft_putstr(inside_quotes);
		free(inside_quotes);
	}
	else if (arg[0] == '$' && ft_strcmp(arg, "$") != 0)
		ft_putstr(get_env_value(arg));
	else if (arg[0] == '$' && ft_strcmp(arg, "$") == 0)
		ft_putchar('$');
	else if (ft_strcmp(arg, "\"\"") != 0 && ft_strcmp(arg, "''") != 0)
		ft_putstr(arg);
	else
		ft_putchar(' ');
}

void	ft_echo(char *line)
{
	char	**arr;
	int		i;
	int		newline;

	arr = parse_input(line);
	i = 1;
	newline = 1;
	if (arr[i] && ft_strcmp(arr[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (arr[i])
	{
		print_argument(arr[i]);
		if (arr[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (newline)
		ft_putchar('\n');
}
