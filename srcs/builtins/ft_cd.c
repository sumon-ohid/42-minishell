/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/26 13:20:20 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setenv(t_data *node, char *name, char *value)
{
	int		i;
	char	*str;
	char	*new_entry;

	i = 0;
	str = ft_strjoin(name, "=", 0);
	if (!str)
		ft_exit(node, -1, "malloc fail in setenv");
	new_entry = ft_strjoin(str, value, 1);
	if (!new_entry)
		ft_exit(node, -1, "malloc fail in setenv");
	free(value);
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], name, ft_strlen(name)) == 0
			&& node->envp[i][ft_strlen(name)] == '=')
		{
			free(node->envp[i]);
			node->envp[i] = new_entry;
			return ;
		}
		i++;
	}
}

char	*ft_getenv(char *name, t_data *node)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], name, len) == 0
			&& node->envp[i][len] == '=')
			return (node->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_current_directory(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
		perror("getcwd failed");
	return (dir);
}

void	change_directory(char *str, t_data *node)
{
	node->home = ft_getenv("HOME", node);
	if (node->home == NULL)
	{
		ft_putstr("minishell: cd: HOME not set\n");
		return ;
	}
	if (str == NULL || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "~") == 0)
		chdir(node->home);
	else if (ft_strcmp(str, "-") == 0)
	{
		chdir(node->oldpwd);
		printf("%s\n", node->oldpwd);
	}
	else
	{
		if (chdir(str) == -1)
		{
			ft_putstr("cd: no such directory: ");
			ft_putstr(str);
			ft_putstr("\n");
			return ;
		}
	}
}

void	ft_cd(char *str, t_data *node)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_current_directory();
	if (oldpwd == NULL)
		ft_exit(node, -1, NULL);
	change_directory(str, node);
	pwd = get_current_directory();
	if (pwd == NULL)
		ft_exit(node, -1, NULL);
	ft_setenv(node, "OLDPWD", oldpwd);
	ft_setenv(node, "PWD", pwd);
}
