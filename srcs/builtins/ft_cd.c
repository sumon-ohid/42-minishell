/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 13:35:47 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char	**new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= old_size)
		return (ptr);
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, old_size);
			free(ptr);
		}
		return (new_ptr);
	}
}

void	ft_setenv(t_data *node, char *name, char *value)
{
	int		i;
	char	*str;
	char	**new_envp;
	char	*new_entry;

	i = 0;
	str = ft_strjoin(name, "=", 0);
	new_entry = ft_strjoin(str, value, 0);
	while (node->envp[i])
	{
		if (ft_strncmp(node->envp[i], name, strlen(name)) == 0
			&& node->envp[i][strlen(name)] == '=')
		{
			node->envp[i] = new_entry;
			return ;
		}
		i++;
	}
	new_envp = ft_realloc(node->envp, 1, sizeof(char *) * (i + 2));
	if (new_envp == NULL)
		exit(1);
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	node->envp = new_envp;
}

char	*get_current_directory(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
		perror("getcwd");
	return (dir);
}

void	change_directory(char *str, t_data *node)
{
	if (str == NULL || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "~") == 0)
		chdir(node->home);
	else if (strcmp(str, "-") == 0)
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
