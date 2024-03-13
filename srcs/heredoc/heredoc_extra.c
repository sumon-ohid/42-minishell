/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:59:41 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 16:10:15 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_signals(char *line, t_data *node)
{
	if (g_signal == CTRL_C)
	{
		free(line);
		g_signal = 0;
		node->last_return = -88;
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

char	*read_and_handle_line(t_data *node)
{
	char	*line;

	line = readline("> ");
	return (handle_signals(line, node));
}

char	*join_line_to_heredoc(char *heredoc, char *line, t_data *node)
{
	heredoc = ft_strjoin(heredoc, line, 1);
	if (!heredoc)
		ft_exit(node, -1, "malloc failed at heredoc");
	heredoc = ft_strjoin(heredoc, "\n", 1);
	if (!heredoc)
		ft_exit(node, -1, "malloc failed at heredoc");
	return (heredoc);
}

char	*handle_envp_in_heredoc(char *heredoc, t_data *node)
{
	char	*temp;

	temp = heredoc;
	heredoc = handle_envp(temp, node);
	if (!heredoc)
		ft_exit(node, -1, "malloc failed at heredoc");
	free(temp);
	return (heredoc);
}

char	*ft_heredoc(t_data *node, t_token *delim)
{
	char	*line;
	char	*heredoc;

	heredoc = ft_strdup("");
	if (!heredoc)
		ft_exit(node, -1, "malloc failed at heredoc");
	mode(node, HEREDOCS);
	while (1)
	{
		line = read_and_handle_line(node);
		if (!line || ft_strcmp(line, delim->str) == 0)
			break ;
		heredoc = join_line_to_heredoc(heredoc, line, node);
		free(line);
	}
	mode(node, NON_INTERACTIVE);
	if (line != NULL)
		free(line);
	if (ft_strstr(heredoc, "$") && delim->quote == NO_QUOTE)
		heredoc = handle_envp_in_heredoc(heredoc, node);
	if (node->last_return == -88)
		return (free(heredoc), NULL);
	return (heredoc);
}
