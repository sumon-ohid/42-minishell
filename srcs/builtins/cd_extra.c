/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:38:37 by msumon            #+#    #+#             */
/*   Updated: 2024/03/11 16:39:35 by msumon           ###   ########.fr       */
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
