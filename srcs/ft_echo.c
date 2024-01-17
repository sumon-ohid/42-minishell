/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 09:53:34 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (ft_strcmp(arg, "\"\"") != 0 && ft_strcmp(arg, "''") != 0)
	{
		ft_putstr(arg);
	}
}

void	ft_echo(char **arr)
{
	int	i;
	int	newline;

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
		{
			ft_putchar(' ');
		}
		i++;
	}
	if (newline)
	{
		ft_putchar('\n');
	}
}
