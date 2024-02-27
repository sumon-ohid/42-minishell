/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:59:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/27 10:55:12 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
}

char	*malloc_heredoc(char *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memset(new_ptr, 0, new_size);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*handle_signals(char *line)
{
	if (g_signal == CTRL_C)
	{
		free(line);
		g_signal = 0;
		return (NULL);
	}
	else if (!line || g_signal == SIGQUIT)
	{
		write(2, "minishell: warning: here-document delimited by end-of-file\n",
			59);
		g_signal = 0;
		return (NULL);
	}
	return (line);
}

char	*append_line_to_heredoc(char *heredoc, char *line, size_t *len,
		t_data *node)
{
	if (heredoc)
	{
		heredoc = malloc_heredoc(heredoc, *len, *len + ft_strlen(line) + 2);
		if (!heredoc)
			ft_exit(node, -1, "malloc failed at heredoc");
		if (*len > 0)
		{
			heredoc = ft_strjoin(heredoc, "\n", 1);
			if (!heredoc)
				ft_exit(node, -1, "malloc failed at heredoc");
		}
		heredoc = ft_strjoin(heredoc, line, 1);
		if (!heredoc)
			ft_exit(node, -1, "malloc failed at heredoc");
	}
	else
	{
		heredoc = malloc(ft_strlen(line) + 1);
		if (!heredoc)
			ft_exit(node, -1, "malloc failed at heredoc");
		ft_strcpy(heredoc, line);
	}
	*len += ft_strlen(line) + 1;
	return (heredoc);
}

char	*ft_heredoc(t_data *node, char *str)
{
	char	*line;
	size_t	len;
	char	*heredoc;

	heredoc = ft_strdup("");
	len = 0;
	mode(node, HEREDOCS);
	while (1)
	{
		line = readline("> ");
		line = handle_signals(line);
		if (!line)
			break ;
		if (ft_strcmp(line, str) == 0)
			break ;
		heredoc = append_line_to_heredoc(heredoc, line, &len, node);
		free(line);
	}
	mode(node, NON_INTERACTIVE);
	if (line != NULL)
		free(line);
	heredoc = ft_strjoin(heredoc, "\n", 1);
	if (!heredoc)
		ft_exit(node, -1, "malloc failed at heredoc");
	return (heredoc);
}
