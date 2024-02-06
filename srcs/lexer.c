/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:51:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/06 15:41:03 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_upgrade_spaces(char *line);

int	entry_check(t_data *node, char *line)
{
	char	**arr;
	t_token	**tokens;
	int		ret_val;

	if (!ft_lexical_checker(line))
		return (2);
	line = ft_upgrade_spaces(line);
	tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	if (!tokens)
	{
		perror("Memory allocation failed");
		return (127);
	}
	arr = parse_input(line);
	if (!arr)
	{
		free(tokens);
		return (127);
	}
	process_words(&tokens, arr, line, node);
	ret_val = executor_init(node, tokens, pipe_counter(line), line);
	free_tokens(tokens);
	free(line);
	free_arr(arr);
	return (ret_val);
}

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
            result[j++] = line[i];
        i++;
    }
    result[j] = '\0';
	free(line);
    return (result);
}


int ft_lexer_error(char *line)
{
	(void)line;
	printf("minishell: syntax error near unexpected token\n");
	return (0);
}

int	ft_check_quotes(char c, int *in_single_quote, int *in_double_quote)
{
    if (c == '\'' && !(*in_double_quote))
        *in_single_quote = !(*in_single_quote);
    else if (c == '\"' && !(*in_single_quote))
        *in_double_quote = !(*in_double_quote);
    return (*in_single_quote || *in_double_quote);
}

int	ft_check_char_sequence(char c, char prev_char, char *line, int i)
{
    if ((c == '|' && prev_char == '|') || 
        (c == '<' && prev_char == '>') || 
        (c == '>' && prev_char == '<') || 
        (c == '|' && prev_char == '>') || 
        (c == '|' && prev_char == '<') || 
        (c == '>' && prev_char == '|') || 
        (c == '<' && prev_char == '|') || 
        (c == '>' && line[i + 1] == ' ' && line[i + 2] == '>') || 
        (c == '<' && line[i + 1] == ' ' && line[i + 2] == '<') || 
        (c == '|' && line[i + 1] == ' ' && line[i + 2] == '|') || 
        (c == '>' && line[i + 1] == '\0') || 
        (c == '<' && line[i + 1] == '\0') || 
        (c == '|' && line[i + 1] == '\0') || 
        (c == '>' && line[i + 1] == ' ' && !(line[i + 2] >= 'A' && line[i + 2] <= 'z')) || 
        (c == '<' && line[i + 1] == ' ' && !(line[i + 2] >= 'A' && line[i + 2] <= 'z')) || 
        (c == '|' && line[i + 1] == ' ' && !(line[i + 2] >= 'A' && line[i + 2] <= 'z')))
    {
        return(ft_lexer_error(line));
    }
    return (1);
}

int	ft_lexical_checker(char *line)
{
    int in_single_quote = 0;
    int in_double_quote = 0;
    char prev_char = '\0';
    int i = 0;

    while (line[i] != '\0')
    {
        char c = line[i];

        if (ft_check_quotes(c, &in_single_quote, &in_double_quote))
            return(ft_lexer_error(line));

        if (!in_single_quote && !in_double_quote)
        {
            if (!ft_check_char_sequence(c, prev_char, line, i))
                return (0);
        }
        prev_char = c;
        i++;
    }
    return (1);
}
