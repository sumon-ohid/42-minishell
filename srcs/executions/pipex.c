/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:21:29 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/22 12:31:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_og_comm(char *og_comm)
{
	if (access(og_comm, X_OK) == 0)
		return (og_comm);
	else
		return (NULL);
}

void	free_poss_paths(char **poss_paths)
{
	int	counter;

	counter = 0;
	while (poss_paths[counter])
	{
		free(poss_paths[counter++]);
	}
	free(poss_paths);
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
	return (check_og_comm(og_comm));
}

char	*pathfinder(char **envp, char *comm, t_data *node)
{
	char	**poss_paths;
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
	poss_paths = ft_split(&envp[counter][i], ':', 0, 0);
	if (!poss_paths)
		ft_exit(node, -1, "malloc failure at pathfinder");
	counter = -1;
	while (poss_paths[++counter])
		poss_paths[counter] = ft_strjoin(poss_paths[counter], comm2, 1);
	return (extract_path(comm2, poss_paths, comm, node));
}

char	**comm_array(t_token *mark, t_data *node)
{
	char *full_comm;
	char **result;
	
	full_comm = mark->str;
	if (mark->quote == NO_QUOTE)
		return (ft_split(full_comm, ' ', 0, 0));
	else
	{
		result = malloc(sizeof(char *) * 2);
		if (!result)
			ft_exit(node, -1, "malloc failure during execution");
		result[0] = ft_strdup(full_comm);
		if (!result[0])
			ft_exit(node, -1, "malloc failure during execution");
		result[1] = NULL;
	}
	return (result);
}

void	extract_find_execute(char **envp, t_token *mark, t_data *node)
{
	char	**comms;
	char	*path;
	int		counter;

	counter = 0;
	comms = comm_array(mark, node);
	if (!comms)
		ft_exit(node, -1, "malloc failure");
	while (comms[counter])
		counter++;
	path = pathfinder(envp, comms[0], node);
	if (ft_strcmp(path, "faill") == 0 || !path)
	{
		ft_free_fds(node);
		nocomm_error(comms[0]);
		free_everything(comms, counter);
		ft_exit(node, 127, NULL);
	}
	execve(path, comms, NULL);
	free_everything(comms, counter);
	ft_exit(node, 127, "execve failed");
}
