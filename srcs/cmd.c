/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/17 16:33:26 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

void	ft_ls(char *dir_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_name);
	if (!dir)
	{
		perror("minishell");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			ft_putstr(entry->d_name);
			ft_putchar(' ');
		}
		entry = readdir(dir);
	}
	ft_putchar('\n');
	closedir(dir);
}

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
	else if (ft_strcmp(arr[0], "ls") == 0)
		ft_ls(".");
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
