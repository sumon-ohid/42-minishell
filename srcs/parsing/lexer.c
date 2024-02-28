/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:51:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/27 09:45:23 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lexer_error(char *line)
{
	free(line);
	write(2, "minishell: syntax error near unexpected token\n", 47);
	return (0);
}

int	check_invalid_sequences(char c, char prev_char, char *line)
{
	if (c == '|' && prev_char == '|')
		return (ft_lexer_error(line));
	else if (c == '<' && prev_char == '>')
		return (ft_lexer_error(line));
	else if (c == '>' && prev_char == '<')
		return (ft_lexer_error(line));
	else if (c == '|' && !prev_char)
		return (ft_lexer_error(line));
	// else if (c == '|' && prev_char == '>')
	// 	return (ft_lexer_error(line));
	else if (c == '|' && prev_char == '<')
		return (ft_lexer_error(line));
	// else if (c == '>' && prev_char == '|')
	// 	return (ft_lexer_error(line));
	// else if (c == '<' && prev_char == '|')
	//	return (ft_lexer_error(line));
	else if (c == '<' && prev_char == '<' && line[2] == '<')
		return (ft_lexer_error(line));
	else if (c == '>' && prev_char == '>' && line[2] == '>')
		return (ft_lexer_error(line));
	return (1);
}

int	check_invalid_endings(char c, char *line, int i)
{
	if (c == '>' && line[i + 1] == '\0')
		return (ft_lexer_error(line));
	else if (c == '<' && line[i + 1] == '\0')
		return (ft_lexer_error(line));
	else if (c == '|' && line[i + 1] == '\0')
		return (ft_lexer_error(line));
	return (1);
}

int	check_invalid_next_chars(char c, char *line, int i)
{
	if (c == '>' && line[i + 1] == ' ' && !(line[i + 2] >= 'A' && line[i
				+ 2] <= 'z'))
		return (ft_lexer_error(line));
	else if (c == '<' && line[i + 1] == ' ' && !(line[i + 2] >= 'A' && line[i
				+ 2] <= 'z'))
		return (ft_lexer_error(line));
	else if (c == '=' && line[i + 1] == ' ')
		return (ft_lexer_error(line));
	return (1);
}

char	*remove_spaces(char *input)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc(ft_strlen(input) + 1);
	if (!line)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
		{
			line[j] = input[i];
			j++;
		}
		i++;
	}
	line[j] = '\0';
	return (line);
}

int	ft_lexical_checker(char *input, int in_single_quote, int in_double_quote,
		char prev_char)
{
	char	c;
	int		i;
	char 	*line;

	i = 0;
	line = remove_spaces(input);
	while ((line[i]) != '\0')
	{
		c = line[i];
		if (c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (c == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (!check_invalid_sequences(c, prev_char, line)
				|| !check_invalid_endings(c, line, i))
			{
				return (0);
			}
		}
		prev_char = c;
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (ft_lexer_error(line));
	free(line);
	return (1);
}
