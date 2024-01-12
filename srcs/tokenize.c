/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:50:09 by sumon             #+#    #+#             */
/*   Updated: 2024/01/12 12:22:51 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	*handle_envp(char *str)
{
	char	*output;

	output = getenv(str + 1);
	if (!output)
		output = ft_strdup("\n");
	// malloc protection
	free(str);
	return (output);
}

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

t_token	*create_token(char *word)
{
	t_token	*new;

	if (!word)
		return (0);
	new = malloc(sizeof(t_token));
	new->previous = NULL;
	new->next = NULL;
	if (word[0] == '$')
		new->str = handle_envp(word); // TODO: account for $?
	else
		new->str = ft_strdup(word);
	// malloc protection
	new->type = 0;
	return (new);
}

t_token	**tokenizer(char *str)
{
	char	**words;
	int		counter;
	t_token	**tokens;
	t_token	*cur;

	words = parse_input(str);
	counter = 0;
	tokens = NULL;
	while (words[counter])
	{
		if (!tokens)
		{
			*tokens = create_token(words[counter]);
			(*tokens)->type = determine_type(words[counter], 0);
		}
		else
		{
			cur = *tokens;
			while (cur->next)
				cur = cur->next;
			cur->next = create_token(words[counter]);
			cur->next->previous = cur;
			cur->next->type = determine_type(words[counter], cur->type);
		}
		counter++;
		// TODO: error management
	}
	return (tokens);
}
