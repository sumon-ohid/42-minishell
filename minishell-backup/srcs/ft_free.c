/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:41 by msumon            #+#    #+#             */
/*   Updated: 2024/01/26 18:16:08 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_tokens(t_token **tokens)
{
	t_token *proxy;
	t_token *previous;

	proxy = *tokens;
	if (!proxy)
		return ;
	while (proxy)
	{
		previous = proxy;
		proxy = proxy->next;
		free(previous->str);
		free_arr(previous->arr);
		free(previous);
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
	perror("minishell: .: filename argument required");
	perror(".: usage: . filename [arguments]");
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
