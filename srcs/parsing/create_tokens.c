/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 20:30:20 by mhuszar          ###   ########.fr       */
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
	{
		free(word);
		parse_error(node, 1, "memory allocation failed at create token", -1);
	}
	new->previous = NULL;
	new->next = NULL;
	new->heredoc_data = NULL;
	new->quote = quote_assigner(node->quote);
	new->str = ft_strdup(word);
	if (!new->str)
	{
		free(word);
		free(new);
		parse_error(node, 1, "memory allocation failed at create token", -1);
	}
	new->type = 0;
	new->exported = node->exported;
	node->exported = false;
	return (new);
}

int	pipe_counter(char *str)
{
	int		counter;
	int		pipes;
	char	quote_char;

	if (!str)
		return (0);
	counter = 0;
	pipes = 0;
	quote_char = 0;
	while (str[counter])
	{
		if ((str[counter] == '\'' || str[counter] == '\"') && !quote_char)
			quote_char = str[counter];
		else if ((str[counter] == '\'' || str[counter] == '\"')
			&& quote_char == str[counter])
			quote_char = 0;
		else if (str[counter] == '|' && !quote_char
			&& counter > 0 && str[counter - 1] != '>')
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
		cur->type = determine_type(word, 0, cur, node);
		tokens[current] = cur;
	}
	else
	{
		while (proxy->next)
			proxy = proxy->next;
		proxy->next = create_token(word, node);
		proxy->next->type = determine_type(word, proxy->type,
				proxy->next, node);
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
