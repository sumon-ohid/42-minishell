/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:41 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 18:41:28 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*void	free_tokens(t_token **tokens, int processes)
{
	t_token	*proxy;
	t_token	*previous;
	int		counter;

	counter = 0;
	while (counter < processes)
	{
		proxy = tokens[counter];
		if (!proxy)
			return ;
		while (proxy)
		{
			previous = proxy;
			proxy = proxy->next;
			free(previous->heredoc_data);
			free(previous->str);
			free(previous);
		}
		counter++;
	}
	free(tokens);
}*/

void	free_tokens(t_token **tokens, int processes, int flag)
{
	t_token	*proxy;
	t_token	*previous;
	int		counter;

	counter = 0;
	while ((counter < processes && flag) || (tokens[counter] && !flag))
	{
		proxy = tokens[counter];
		while (proxy)
		{
			previous = proxy;
			proxy = proxy->next;
			if (previous->heredoc_data)
				free(previous->heredoc_data);
			if (previous->str)
				free(previous->str);
			free(previous);
		}
		counter++;
	}
	free(tokens);
}

void	error_quit(int fd, int *tomlo, char *str)
{
	if (fd)
		close(fd);
	if (tomlo)
	{
		close(tomlo[0]);
		close(tomlo[1]);
	}
	if (str)
		free(str);
	ft_putstr_fd("minishell: .: filename argument required", 2);
	ft_putstr_fd(".: usage: . filename [arguments].\n", 2);
	exit(2);
}

char	**free_everything(char **arr, int m_ctr)
{
	int	counter;

	counter = 0;
	while (counter < m_ctr && arr[counter])
	{
		free(arr[counter]);
		counter++;
	}
	free(arr);
	return (NULL);
}
