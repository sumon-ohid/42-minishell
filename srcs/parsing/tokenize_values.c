/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by msumon            #+#    #+#             */
/*   Updated: 2024/03/11 16:40:17 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	determine_type(char *word, int prev_type, int quote)
{
	if (!word)
		return (0);
	else if (ft_strcmp("<", word) == 0 && quote == NO_QUOTE)
		return (REDIR_IN);
	else if ((ft_strcmp(">", word) == 0 || ft_strcmp(">|", word) == 0)
		&& quote == NO_QUOTE)
		return (REDIR_OUT);
	else if (ft_strcmp("<<", word) == 0 && quote == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strcmp(">>", word) == 0 && quote == NO_QUOTE)
		return (REDIR_OUT_APPEND);
	else if (ft_strcmp("|", word) == 0 && quote == NO_QUOTE)
		return (PIPE);
	else if (check_builtins(word) == 2 && (!prev_type || prev_type == INFILE
			|| prev_type == DELIM))
		return (EXPORT);
	else if (check_builtins(word) == 0 && (!prev_type || prev_type == INFILE
			|| prev_type == DELIM))
		return (BUILTIN);
	else
		return (check_prevs(word, prev_type));
}

int	check_builtins(char *word)
{
	if (!word)
		return (-1);
	else if (ft_strcmp(word, "cd") == 0)
		return (0);
	else if (ft_strcmp(word, "echo") == 0)
		return (0);
	else if (ft_strcmp(word, "env") == 0)
		return (0);
	else if (ft_strcmp(word, "clear") == 0)
		return (0);
	else if (ft_strcmp(word, "pwd") == 0)
		return (0);
	else if (ft_strcmp(word, "exit") == 0)
		return (0);
	else if (ft_strcmp(word, "export") == 0)
		return (2);
	else if (ft_strcmp(word, "unset") == 0)
		return (0);
	else
		return (-1);
}

int	check_assign(char *word)
{
	int	counter;

	counter = 0;
	if (!word)
		return (0);
	while (word[counter])
	{
		if (word[counter] == '=')
			return (1);
		counter++;
	}
	return (0);
}

int	check_prevs(char *word, int prev_type)
{
	if (!word)
		return (0);
	else if (check_assign(word) && (prev_type == EXPORT || prev_type == SET))
		return (SET);
	else if (prev_type == HEREDOC)
		return (DELIM);
	else if (prev_type == REDIR_OUT)
		return (OUTFILE);
	else if (prev_type == REDIR_OUT_APPEND)
		return (OUTFILE_APPEND);
	else if (prev_type == REDIR_IN)
		return (INFILE);
	else if (prev_type == BUILTIN || prev_type == COMMAND || prev_type == FLAG
		|| prev_type == EXPORT)
		return (FLAG);
	else
		return (COMMAND);
}
