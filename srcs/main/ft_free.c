/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/08 13:55:15 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

//dokens is really double array, freeing needs to be changed somehow!!!!
void	free_tokens(t_token **tokens)
{
	t_token	*proxy;
	t_token	*previous;

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
	ft_putstr_fd("minishell: .: filename argument required", 2);
	ft_putstr_fd(".: usage: . filename [arguments]", 2);
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
