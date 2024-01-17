/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 09:31:29 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **arr)
{
	int		i;
	int		newline;
	char	*inside_quotes;

	i = 1;
	newline = 1;
	if (arr[i] && ft_strcmp(arr[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (arr[i])
	{
		if ((arr[i][0] == '"' && arr[i][ft_strlen(arr[i]) - 1] == '"')
			|| (arr[i][0] == '\'' && arr[i][ft_strlen(arr[i]) - 1] == '\''))
		{
			inside_quotes = ft_strndup(arr[i] + 1, ft_strlen(arr[i]) - 2);
			ft_putstr(inside_quotes);
			free(inside_quotes);
		}
		else if (ft_strcmp(arr[i], "\"\"") != 0 && ft_strcmp(arr[i], "''") != 0)
			ft_putstr(arr[i]);
		if (arr[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (newline)
		ft_putchar('\n');
}
