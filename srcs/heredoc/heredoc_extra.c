/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:59:41 by msumon            #+#    #+#             */
/*   Updated: 2024/03/04 12:51:39 by msumon           ###   ########.fr       */
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

char	*handle_signals(char *line, t_data *node)
{
	if (g_signal == CTRL_C)
	{
		free(line);
		g_signal = 0;
		node->last_return = -88; //not used yet
		return (NULL);
	}
	else if (!line)
	{
		write(2, "minishell: warning: here-document delimited by end-of-file\n",
			59);
		g_signal = 0;
		return (NULL);
	}
	return (line);
}

void	remove_quotes(char *temp)
{
	int	i;
	int	j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(temp);
	while (i < len)
	{
		if (temp[i] == '\"' || temp[i] == '\'')
			i++;
		temp[j] = temp[i];
		i++;
		j++;
	}
	temp[j] = '\0';
}

char	*put_quotes_back(char *heredoc, char *line)
{
	char *new_heredoc;

	(void)line;
	new_heredoc = malloc(ft_strlen(heredoc) + 3);
	if (!new_heredoc)
		return (NULL);
	new_heredoc = ft_strjoin("\"", heredoc, 0);
	if (!new_heredoc)
		return (NULL);
	new_heredoc = ft_strjoin(new_heredoc, "\"", 1);
	if (!new_heredoc)
		return (NULL);
	free(heredoc);
	return (new_heredoc);
}

char	*append_line_to_heredoc(char *heredoc, char *line, size_t *len,
		t_data *node)
{
	char	*temp;

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
	if (ft_strstr(heredoc, "$") && !ft_strstr(node->input_line, "\""))
	{
		temp = heredoc;
		heredoc = handle_envp(temp, node);
		free(temp);
	}
	*len = ft_strlen(heredoc);
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
		line = handle_signals(line, node);
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
	if (node->last_return == -88)
		return (free(heredoc), NULL);
	return (heredoc);
}
