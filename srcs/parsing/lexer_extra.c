/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:54 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 14:45:25 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_input(char *line)
{
	char	**tokens;

	tokens = ft_split(line, '|', 0, 0);
	if (!tokens)
	{
		write(2, "Allocation error\n", 17);
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

char	*ft_upgrade_spaces(char *line, int i, int j, int in_quotes)
{
	char	*result;

	result = malloc(strlen(line) * 3 + 1);
	if (!result)
		ft_putstr_fd("Memory allocation failed", EXIT_FAILURE);
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
