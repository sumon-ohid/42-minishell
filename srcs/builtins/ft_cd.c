/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/03/07 09:28:07 by msumon           ###   ########.fr       */
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
	free(new_entry);
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

int	change_directory(char *str, t_data *node)
{
	if (str == NULL)
	{
		node->home = ft_getenv("HOME", node);
		if (node->home == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			node->last_return = -99;
			return (1);
		}
		else
			chdir(node->home);
		return (0);
	}
	else if (ft_strcmp(str, "-") == 0)
	{
		chdir(node->oldpwd);
		printf("%s\n", node->oldpwd);
		return (0);
	}
	else if (chdir(str) == -1)
	{
		ft_putstr_fd("minishell: cd: no such file or directory\n", 2);
		return (node->last_return = -99, 1);
	}
	return (0);
}

int	ft_cd(char *str, t_data *node)
{
	char	*oldpwd;
	char	*pwd;
	int		ret;

	ret = 0;
	oldpwd = get_current_directory();
	if (oldpwd == NULL)
		ft_exit(node, -1, "getcwd failed");
	ret = change_directory(str, node);
	pwd = get_current_directory();
	if (pwd == NULL)
		ft_exit(node, -1, "getcwd failed");
	ft_setenv(node, "OLDPWD", oldpwd);
	ft_setenv(node, "PWD", pwd);
	return (ret);
}
