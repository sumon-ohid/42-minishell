/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:59:41 by msumon            #+#    #+#             */
/*   Updated: 2024/02/20 16:29:03 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*append_line_to_heredoc(char *heredoc, char *line, size_t *len)
{
	char	*tmp;

	if (heredoc)
	{
		tmp = ft_realloc_heredoc(heredoc, *len, *len + ft_strlen(line) + 2);
		if (!tmp)
			handle_error("Realloc failed at Heredoc", 1);
		heredoc = tmp;
		if (*len > 0)
			heredoc = ft_strjoin(heredoc, "\n", 0);
		heredoc = ft_strjoin(heredoc, line, 0);
	}
	else
	{
		heredoc = malloc(ft_strlen(line) + 1);
		if (!heredoc)
			handle_error("Malloc failed at Heredoc", 1);
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

	heredoc = NULL;
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
		add_history(line);
		heredoc = append_line_to_heredoc(heredoc, line, &len);
		free(line);
	}
	mode(node, NON_INTERACTIVE);
	if (line != NULL)
		free(line);
	heredoc = ft_strjoin(heredoc, "\n", 0);
	return (heredoc);
}
