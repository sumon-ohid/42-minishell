/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by msumon             #+#    #+#             */
/*   Updated: 2024/01/17 16:34:52 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	determine_type(char *word, int prev_type)
{
	(void)prev_type;
	if (!word)
		return (0);
	if (ft_strcmp("<", word) == 0)
		return (REDIR_IN);
	if (ft_strcmp(">", word) == 0)
		return (REDIR_OUT);
	if (ft_strcmp(">>", word) == 0)
		return (REDIR_OUT_APPEND);
	if (ft_strcmp("|", word) == 0)
		return (PIPE);
	return (0);
}

// TODO: account for $?
// malloc protection
t_token	*create_token(char *word)
{
	t_token	*new;

	if (!word)
		return (0);
	new = malloc(sizeof(t_token));
	new->previous = NULL;
	new->next = NULL;
	if (word[0] == '$')
		new->str = handle_envp(word);
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

t_token	*create_and_link_token(t_token *cur, char *word)
{
	if (!cur)
	{
		cur = create_token(word);
		cur->type = determine_type(word, 0);
	}
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = create_token(word);
		cur->next->previous = cur;
		cur->next->type = determine_type(word, cur->type);
	}
	return (cur);
}

void	process_words(t_token **tokens, char **words, char *str)
{
	int		counter;
	int		counter2;

	counter = 0;
	counter2 = 0;
	while (counter2 < pipe_counter(str))
	{
		while (words[counter] && ft_strcmp(words[counter], "|") != 0)
		{
			tokens[counter2] = create_and_link_token(tokens[counter2],
					words[counter]);
			counter++;
			// TODO: error management
		}
		counter2++;
		counter++;
	}
}
