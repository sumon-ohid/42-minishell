/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 15:37:04 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	determine_type(char *word, int prev_type)
{
	if (!word)
		return (0);
	else if (ft_strcmp("<", word) == 0)
		return (REDIR_IN);
	else if (ft_strcmp(">", word) == 0)
		return (REDIR_OUT);
	else if (ft_strcmp("<<", word) == 0)
		return (HEREDOC);
	else if (ft_strcmp(">>", word) == 0)
		return (REDIR_OUT_APPEND);
	else if (ft_strcmp("|", word) == 0)
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
	new->previous = NULL;
	new->next = NULL;
	new->arr = NULL;
	if (ft_strstr(word, "$"))
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

	if (!str)
		return (0);
	counter = 0;
	pipes = 0;
	while (str[counter])
	{
		if (str[counter] == '|')
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
		cur->type = determine_type(word, 0);
		tokens[current] = cur;
	}
	else
	{
		while (proxy->next)
			proxy = proxy->next;
		proxy->next = create_token(word, node);
		proxy->next->type = determine_type(word, proxy->type);
	}
}

void	process_words(t_token ***origin, char **units, char *str, t_data *node)
{
	int		counter;
	int		counter2;
	char	**words;

	counter = 0;
	counter2 = 0;
	while (counter2 < pipe_counter(str))
	{
		words = ft_split(units[counter2], ' ', 0, 0);
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
