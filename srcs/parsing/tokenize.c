/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by msumon            #+#    #+#             */
/*   Updated: 2024/02/19 11:40:20 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	determine_type(char *word, int prev_type, int quote)
{
	if (!word)
		return (0);
	else if (ft_strcmp("<", word) == 0 && quote == NO_QUOTE)
		return (REDIR_IN);
	else if (ft_strcmp(">", word) == 0 && quote == NO_QUOTE)
		return (REDIR_OUT);
	else if (ft_strcmp("<<", word) == 0 && quote == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strcmp(">>", word) == 0 && quote == NO_QUOTE)
		return (REDIR_OUT_APPEND);
	else if (ft_strcmp("|", word) == 0 && quote == NO_QUOTE)
		return (PIPE);
	else if (check_builtins(word) == 0)
		return (BUILTIN);
	else
		return (check_prevs(word, prev_type));
}

// TODO: account for $?
// malloc protection
t_token	*create_token(char *word, t_data *node)
{
	t_token	*new;

	if (!word)
		return (0);
	new = malloc(sizeof(t_token));
	if (!new)
		handle_error("Memory allocation failed at create token", 1);
	new->previous = NULL;
	new->next = NULL;
	new->arr = NULL;
	new->quote = quote_assigner(node->line_temp, word);
	if (ft_strstr(word, "$") && new->quote != SINGLE_QUOTE)
		new->str = handle_envp(word, node);
	else
		new->str = ft_strdup(word);
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

void	process_words(t_token ***origin, char **units, char *str, t_data *node)
{
	int		counter;
	int		counter2;
	char	**words;

	counter = 0;
	counter2 = 0;
	node->line_temp = str;
	while (counter2 < pipe_counter(str))
	{
		words = ft_split_special(units[counter2], ' ', 'X', 0);
		while (words[counter])
		{
			create_and_link_token(origin, counter2, words[counter], node);
			counter++;
		}
		counter2++;
		counter = 0;
		ft_free_array(words);
	}
}
