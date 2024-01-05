/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/05 14:52:38 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_echo(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		ft_putstr(arr[i]);
		ft_putchar(' ');
		i++;
	}
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

void	ft_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}
}

void	ft_execve(char **arr, char *str)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env;

	pid = fork();
	if (pid == 0)
	{
		path = ft_strjoin(str, "|", 0);
		path = ft_strjoin(path, arr[0], 1);
		env = (char **)malloc(sizeof(char *) * 2);
		env[0] = ft_strjoin("PATH=", str, 0);
		env[1] = NULL;
		if (execve(path, arr, env) == -1)
			ft_putstr("command not found\n");
	}
	else
		wait(&status);
}

void	ft_ls(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
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
	else if (ft_strcmp(arr[0], "ls") == 0)
		ft_ls();
	else if (ft_strcmp(arr[0], "pwd") == 0)
	{
		getcwd(str, 1024);
		ft_putstr(str);
		ft_putchar('\n');
	}
	else if (ft_strcmp(arr[0], "exit") == 0)
		exit(0);
	else
		ft_execve(arr, str);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
