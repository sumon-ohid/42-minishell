/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:54 by msumon            #+#    #+#             */
/*   Updated: 2024/02/26 13:42:38 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_input(char *line)
{
	char	**tokens;

	tokens = ft_split_special(line, '|', 'P', 0);
	if (!tokens)
		handle_error("Memory allocation failed at parse input", 1);
	return (tokens);
}

//TODO: somehow we have to replace handle error with ft_exit, but for that we have to move node here
char	*ft_upgrade_spaces(char *line, int i, int j, int in_quotes)
{
	char	*result;

	result = malloc(strlen(line) * 3 + 1);
	if (!result)
		handle_error("Memory allocation failed at upgrade_spaces", 1);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && (line[i] == '<' || line[i] == '>'))
		{
			result[j++] = ' ';
			result[j++] = line[i];
			if (line[i + 1] == line[i])
				result[j++] = line[i++];
			result[j++] = ' ';
		}
		else
			result[j++] = line[i];
		i++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

int	quote_assigner(char *big, char *little)
{
	char	*res;

	res = ft_quote_detector(big, little);
	if (res == NULL)
		return (NO_QUOTE);
	else if (*res == '\'')
		return (SINGLE_QUOTE);
	else if (*res == '\"')
		return (DOUBLE_QUOTE);
	else
		return (NO_QUOTE);
}
