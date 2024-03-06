/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:40:57 by msumon            #+#    #+#             */
/*   Updated: 2024/03/06 14:22:38 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_counter(t_token *tokens)
{
	t_token	*proxy;
	int		counter;

	proxy = tokens;
	counter = 0;
	while (proxy)
	{
		if (proxy->type == HEREDOC)
			counter++;
		proxy = proxy->next;
	}
	return (counter);
}

int	check_for_heredoc(t_data *node, t_token **tokens, int processes)
{
	t_token	*proxy;
	int		counter;

	counter = 0;
	while (counter < processes)
	{
		proxy = tokens[counter];
		while (proxy)
		{
			if (proxy->type == HEREDOC && proxy->next)
			{
				proxy->heredoc_data = ft_heredoc(node, proxy->next->str);
				if (!proxy->heredoc_data)
				{
					free_tokens(tokens, processes);
					ft_free_array(node->arr);
					free(node->input_line);
					return (0);
				}
			}
			proxy = proxy->next;
		}
		counter++;
	}
	return (1);
}

int		room_in_pipe(int *tomlo, t_data *node)
{
	int	return_val;
	int	taken_space;

	return_val = ioctl(tomlo[0], FIONREAD, &taken_space);
	if (return_val == -1)
	{
		close(tomlo[0]);
		close(tomlo[1]);
		free(tomlo);
		ft_exit(node, -1, "pipe checking failed");
	}
	if (taken_space > 500)
		return (0);
	else
		return (1);
}

void	write_in_chunks(char *text, size_t len, int *tomlo, t_data *node)
{
	while (len)
	{
		if (ft_strlen(text) > 5)
		{
			write(tomlo[1], text, 5);
			text = text + 5;
		}
		else
		{
			write(tomlo[1], text, ft_strlen(text));
			return ;
		}
		if (!room_in_pipe(tomlo, node))
			break ;
		len = ft_strlen(text);
	}
}

void	read_from_heredoc(t_token *heredoc, t_data *node)
{
	int		*tomlo;
	char 	*text;
	size_t	len;
	int		pid;

	tomlo = malloc(sizeof(int) * 2);
	if (!tomlo)
		ft_exit(node, -1, "malloc at heredoc failed");
	if (pipe(tomlo) == -1)
	{
		free(tomlo);
		ft_exit(node, -1, "pipe creation for heredoc failed");
	}
	pid = fork();
	if (pid == -1)
		ft_exit(node, -1, "forking failed at heredoc");
	else if (pid != 0)
	{
		dup2(tomlo[0], STDIN_FILENO);
		close(tomlo[0]);
		close(tomlo[1]);
		free(tomlo); //why does not freeeing tomlo not leak here?????
		return ;
	}
	else if (pid == 0)
	{
		text = heredoc->heredoc_data;
		len = ft_strlen(text);
		write_in_chunks(text, len, tomlo, node);
		close(tomlo[0]);
		close(tomlo[1]);
		free(tomlo);
		ft_exit(node, 0, NULL);
	}
}
//write(tomlo[1], heredoc->heredoc_data, ft_strlen(heredoc->heredoc_data));
/*
int	write_in_chunks(char **text, int *tomlo)
{
	if (ft_strlen(*text) > 500)
	{
		write(tomlo[1], *text, 500);
		*text = *text + 500;
		return (0);
	}
	else
	{
		write(tomlo[1], *text, ft_strlen(*text));
		return (1);
	}
}

void	read_from_heredoc(t_token *heredoc, t_data *node)
{
	int		done;
	int		*tomlo;
	char 	*text;

	done = 0;
	text = heredoc->heredoc_data;
	while (!done)
	{
		tomlo = malloc(sizeof(int) * 2);
		if (!tomlo)
			ft_exit(node, -1, "malloc at heredoc failed");
		if (pipe(tomlo) == -1)
		{
			free(tomlo);
			ft_exit(node, -1, "pipe creation for heredoc failed");
		}
		dup2(tomlo[0], STDIN_FILENO);
		done = write_in_chunks(&text, tomlo);
		close(tomlo[0]);
		close(tomlo[1]);
		free(tomlo);
	}
}*/
