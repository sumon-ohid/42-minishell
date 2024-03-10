/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by msumon            #+#    #+#             */
/*   Updated: 2024/03/10 14:41:31 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *word, t_data *node)
{
	t_token	*new;

	if (!word)
		return (0);
	new = malloc(sizeof(t_token));
	if (!new)
		ft_exit(node, -1, "memory allocation failed at create token");
	new->previous = NULL;
	new->next = NULL;
	new->arr = NULL;
	new->heredoc_data = NULL;
	new->quote = quote_assigner(node->quote);
	new->str = ft_strdup(word);
	if (!new->str)
		ft_early_exit(node, -1, "memory allocation failed at create token");
	new->type = 0;
	return (new);
}

int	pipe_counter(char *str)
{
	int	counter;
	int	pipes;
	int	in_quotes;

	if (!str)
		return (0);
	counter = 0;
	pipes = 0;
	in_quotes = 0;
	while (str[counter])
	{
		if ((str[counter] == '\'' || str[counter] == '\"') && !in_quotes)
			in_quotes = 1;
		else if ((str[counter] == '\'' || str[counter] == '\"') && in_quotes)
			in_quotes = 0;
		else if (str[counter] == '|' && !in_quotes)
			pipes++;
		counter++;
	}
	return (pipes + 1);
}

void	create_and_link_token(t_token ***origin, int current, char *word,
		t_data *node)
{
	t_token	*proxy;
	t_token	*cur;
	t_token	**tokens;

	tokens = *origin;
	cur = tokens[current];
	proxy = cur;
	if (!cur)
	{
		cur = create_token(word, node);
		cur->type = determine_type(word, 0, cur->quote);
		tokens[current] = cur;
	}
	else
	{
		while (proxy->next)
			proxy = proxy->next;
		proxy->next = create_token(word, node);
		proxy->next->type = determine_type(word, proxy->type,
				proxy->next->quote);
	}
}
int	quote_assigner(char quote)
{
	if (quote == 0)
		return (NO_QUOTE);
	else if (quote == '\'')
		return (SINGLE_QUOTE);
	else if (quote == '\"')
		return (DOUBLE_QUOTE);
	else
		return (NO_QUOTE);
}

int	ft_lexer_error(char *line)
{
	free(line);
	write(2, "minishell: syntax error near unexpected token\n", 47);
	return (0);
}

