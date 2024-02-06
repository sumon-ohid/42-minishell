/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:51:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/06 14:49:43 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char *ft_upgrade_spaces(char *line)
{
	//do the thing (except for " and ')
	//free the line at the end because new version will replace it
	int i;
    int in_quotes;
    char *result;
    int j;
	
	i = 0;
	j = 0;
	in_quotes = 0;
	result = malloc(strlen(line) * 3 + 1);
	if (!result)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
    while (line[i])
    {
        if (line[i] == '"' || line[i] == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && (line[i] == '<' || line[i] == '>'))
        {
            result[j++] = ' ';
            result[j++] = line[i];
            if (line[i + 1] == line[i]) // Handle '<<' and '>>'
            {
                i++;
                result[j++] = line[i];
            }
            result[j++] = ' ';
        }
        else
        {
            result[j++] = line[i];
        }
        i++;
    }
    result[j] = '\0';
	free(line);
    return (result);
}


int ft_lexer_error(char *line)
{
	(void)line;
	printf("minishell: syntax error near unexpected token `newline'\n");
	return (0);
}

int	ft_lexical_checker(char *line)
{
	int in_single_quote;
	int in_double_quote;
	char prev_char;
	char c;
	int i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while ((line[i]) != '\0')
	{
		c = line[i];
		if (c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (c == '\"' && !in_single_quote)
	    	in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (c == '|' && prev_char == '|')
				return(ft_lexer_error(line));
			else if (c == '<' && prev_char == '>')
				return(ft_lexer_error(line));
			else if (c == '>' && prev_char == '<')
				return(ft_lexer_error(line));
			else if (c == '|' && prev_char == '>')
				return(ft_lexer_error(line));
			else if (c == '|' && prev_char == '<')
				return(ft_lexer_error(line));
			else if (c == '>' && prev_char == '|')
				return(ft_lexer_error(line));
			else if (c == '<' && prev_char == '|')
				return(ft_lexer_error(line));
			else if (c == '>' && line[i + 1] == ' ' && line[i + 2] == '>')
				return(ft_lexer_error(line));
			else if (c == '<' && line[i + 1] == ' ' && line[i + 2] == '<')
				return(ft_lexer_error(line));
			else if (c == '|' && line[i + 1] == ' ' && line[i + 2] == '|')
				return(ft_lexer_error(line));
			else if (c == '>' && line[i + 1] == '\0')
				return(ft_lexer_error(line));
			else if (c == '<' && line[i + 1] == '\0')
				return(ft_lexer_error(line));
			else if (c == '|' && line[i + 1] == '\0')
				return(ft_lexer_error(line));
		}
		prev_char = c;
		i++;
	}
	if (in_single_quote || in_double_quote)
		return(ft_lexer_error(line));
	return (1);
}
