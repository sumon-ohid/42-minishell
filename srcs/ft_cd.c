/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/01/24 21:49:30 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

char **ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    char **new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    else if (!ptr)
    {
        return malloc(new_size);
    }
    else if (new_size <= old_size)
    {
        return ptr;
    }
    else
    {
        new_ptr = malloc(new_size);
        if (new_ptr)
        {
           ft_memcpy(new_ptr, ptr, old_size);
            free(ptr);
        }
        return new_ptr;
    }
}

void	ft_setenv(t_data *node, char *name, char *value)
{
	int		i;
	char 	*str;
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
	{
		perror("realloc");
		exit(1);
	}
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	node->envp = new_envp;
}

void	ft_cd(char *str, t_data *node)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (str == NULL)
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
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	ft_setenv(node, "OLDPWD", oldpwd);
	ft_setenv(node, "PWD", pwd);
}
