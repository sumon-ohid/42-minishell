/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:21:29 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/11 21:20:28 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_og_comm(char *og_comm, t_data *node)
{
	char	*result;

	if (access(og_comm, X_OK) == 0)
	{
		result = ft_strdup(og_comm);
		if (!result)
		{
			ft_free_fds(node);
			ft_exit(node, -1, "malloc failure in pathfinder");
		}
		return (result);
	}
	else
		return (NULL);
}

char	*extract_path(char *comm2, char **poss_paths, char *og_comm,
		t_data *node)
{
	int		counter;
	char	*res;

	if (comm2 != NULL)
	{
		free(comm2);
		comm2 = NULL;
	}
	counter = 0;
	while (poss_paths[counter])
	{
		if (access(poss_paths[counter], X_OK) == 0)
		{
			res = ft_strdup(poss_paths[counter]);
			free_poss_paths(poss_paths);
			if (!res)
				ft_exit(node, -1, "malloc failure at pathfinder");
			return (res);
		}
		counter++;
	}
	free_poss_paths(poss_paths);
	return (check_og_comm(og_comm, node));
}

char	*pathfinder(char **envp, char *comm, t_data *node)
{
	char	**p_paths;
	int		counter;
	char	*comm2;
	int		i;

	i = 0;
	comm2 = ft_strjoin("/", comm, 0);
	if (!comm2)
		ft_exit(node, -1, "malloc failure at pathfinder");
	counter = 0;
	while (envp[counter] && (!ft_strstr(envp[counter], "PATH")
			|| ft_strstr(envp[counter], "_PATH")))
		counter++;
	if (!envp[counter])
		return (free(comm2), "faill");
	while (envp[counter][i] && envp[counter][i] != '/')
		i++;
	p_paths = ft_split(&envp[counter][i], ':', 0, 0);
	if (!p_paths)
		ft_exit(node, -1, "malloc failure at pathfinder");
	counter = -1;
	while (p_paths[++counter])
		p_paths[counter] = ft_strjoin_node(p_paths[counter], comm2, 1, node);
	return (extract_path(comm2, p_paths, comm, node));
}

void	extract_find_execute(char **envp, char **comms, t_data *node)
{
	char	*path;
	int		counter;

	counter = 0;
	path = pathfinder(envp, comms[0], node);
	if (ft_strcmp(path, "faill") == 0 || !path)
	{
		ft_free_fds(node);
		nocomm_error(comms[0]);
		free(comms);
		ft_exit(node, 127, NULL);
	}
	close(node->std_in);
	close(node->std_out);
	execve(path, comms, node->envp);
	directory_error(comms[0]);
	if (node->processes > 1)
		ft_free_fds(node);
	free(comms);
	free(path);
	ft_exit(node, 126, NULL);
}
