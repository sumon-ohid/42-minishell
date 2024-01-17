/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/17 09:38:44 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_input(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ', 0, 0);
	if (!tokens)
	{
		write(2, "Allocation error\n", 17);
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

void	entry_check2(char **arr, char *line, int i)
{
	if (ft_strcmp(arr[0], "cd") == 0)
		ft_cd(arr[1]);
	else if (ft_strcmp(arr[0], "echo") == 0)
		ft_echo(arr);
	else if (ft_strcmp(arr[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(arr[0], "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(arr[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(arr[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(arr[0], "exit") == 0)
		exit(0);
	else
		printf("%s : command not found.\n", line);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	entry_check(char *str, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	(void)str;
	arr = parse_input(line);
	if (!arr)
		return ;
	entry_check2(arr, line, i);
}
