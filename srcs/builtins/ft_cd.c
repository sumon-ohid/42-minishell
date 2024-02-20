/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/20 14:20:49 by msumon           ###   ########.fr       */
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
	new_entry = ft_strjoin(str, value, 1);
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
		exit(1);
	change_directory(str, node);
	pwd = get_current_directory();
	if (pwd == NULL)
		exit(1);
	ft_setenv(node, "OLDPWD", oldpwd);
	ft_setenv(node, "PWD", pwd);
}
