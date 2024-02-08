/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:21:29 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/07 13:38:33 by msumon           ###   ########.fr       */
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

char	*extract_path(char *comm2, char **poss_paths, char *og_comm)
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
			return (res);
		}
		counter++;
	}
	free_poss_paths(poss_paths);
	return (check_og_comm(og_comm));
}

char	*pathfinder(char **envp, char *comm)
{
	char	**poss_paths;
	int		counter;
	char	*comm2;
	int		i;

	i = 0;
	comm2 = ft_strjoin("/", comm, 0);
	if (!comm2)
		return ("faill");
	counter = 0;
	while ((!ft_strstr(envp[counter], "PATH") || ft_strstr(envp[counter],
				"_PATH")) && envp[counter])
		counter++;
	while (envp[counter][i] && envp[counter][i] != '/')
		i++;
	poss_paths = ft_split(&envp[counter][i], ':', 0, 0);
	if (!poss_paths)
	{
		free(comm2);
		return ("faill");
	}
	counter = -1;
	while (poss_paths[++counter])
		poss_paths[counter] = ft_strjoin(poss_paths[counter], comm2, 1);
	return (extract_path(comm2, poss_paths, comm));
}

void	extract_find_execute(char **envp, char *full_comm)
{
	char	**comms;
	char	*path;
	int		counter;

	counter = 0;
	comms = ft_split(full_comm, ' ', 0, 0);
	if (!comms)
		exit(1);
	while (comms[counter])
		counter++;
	path = pathfinder(envp, comms[0]);
	if (ft_strcmp(path, "faill") == 0 || !path)
	{
		if (!path)
			printf("minishell: %s: command not found\n", comms[0]);
		else
			printf("Error: malloc failure\n");
		free_everything(comms, counter);
		exit(127);
	}
	execve(path, comms, NULL);
	free_everything(comms, counter);
	error_quit(0, 0, path);
}