/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:40:57 by msumon            #+#    #+#             */
/*   Updated: 2024/02/06 12:08:40 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	*ft_realloc_heredoc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (malloc(1));
	}
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*ft_heredoc(char *str)
{
	char	*line;
	size_t	len;
	char	*tmp;

	char *heredoc; // this will hold the final string
	heredoc = NULL;
	len = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, str) == 0)
			break ;
		if (heredoc)
		{
			tmp = ft_realloc_heredoc(heredoc, len, len + ft_strlen(line) + 2);
			if (!tmp)
			{
				free(heredoc);
				free(line);
				return (NULL);
			}
			heredoc = tmp;
			if (len > 0)
				heredoc = ft_strjoin(heredoc, "\n", 0);
			heredoc = ft_strjoin(heredoc, line, 0);
		}
		else
		{
			heredoc = malloc(ft_strlen(line) + 1);
			if (!heredoc)
			{
				free(line);
				return (NULL);
			}
			ft_strcpy(heredoc, line);
		}
		len += ft_strlen(line) + 1;
		free(line);
	}
	return (heredoc);
}

int	heredoc_counter(t_token *tokens)
{
	t_token *proxy;
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

void check_for_heredoc(t_token **tokens, int processes)
{
	t_token *proxy;
	//int		doc_num;
	int		counter;

	//doc_num = heredoc_counter(tokens);
	//if (!doc_num)
		//return ;
	counter = 0;
	while (counter < processes)
	{
		proxy = tokens[counter];
		while (proxy)
		{
			if (proxy->type == HEREDOC && proxy->next)
			{
				proxy->heredoc_data = ft_heredoc(proxy->next->str);
				if (!proxy->heredoc_data)
					exit(EXIT_FAILURE);
			}
			proxy = proxy->next;
		}
		counter++;
	}
}

void	read_from_heredoc(t_token *heredoc)
{
	int	tomlo[2];

	pipe(tomlo); //protect this??
	dup2(tomlo[0], STDIN_FILENO);
	close(tomlo[0]);
	write(tomlo[1], heredoc->heredoc_data, ft_strlen(heredoc->heredoc_data));
	close(tomlo[1]);
	free(heredoc->heredoc_data);
}
