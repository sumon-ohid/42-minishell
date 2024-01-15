/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/15 13:36:17 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(void)
{
	extern char	**environ;
	int i;
	
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

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
		{
			ft_putstr(arr[i]);
		}
		if (arr[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (newline)
		ft_putchar('\n');
}

void	ft_cd(char *str)
{
	if (str)
	{
		if (chdir(str) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr("\n");
		}
	}
	else
		chdir("/Users/new_dir");
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr(pwd);
	ft_putchar('\n');
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

void	entry_check(char *str, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	(void)str;
	arr = parse_input(line);
	if (!arr)
		return ;
	if (ft_strcmp(arr[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(arr[0], "cd") == 0)
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
	else
		printf("%s : command not found.\n", line);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
