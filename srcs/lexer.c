/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:51:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/06 11:07:28 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char *ft_upgrade_spaces(line)
{
	//do the thing (except for " and ')
	//free the line at the end because new version will replace it
}


// we have to iterate through line and implement the following here:
	// 1. check if a ' or " has started,
	//	they also have a maching sign that closes it
	// 2. There are no two pipes following each other, like | | or
	//	|| (we dont implement OR operator)
	// 3. There are no two redirections following each other,
	//	like > > or < < or >> >> etc. (BUT >> is okay)
	// 4. there is no pipe without anything following it, like ls | ls |
	// 5. there is no redirection without anything following it, like ls | ls  >
	// 6. there should not be any spaces sorrounding a = sign
	// 7. of course all of the above is allowed to happen inside quotes ("like this" 'or this')
	// If any error of the above happens,
	//	display "Syntax error near unexpected token", free line, return 0
	// Otherwise: return 1
int ft_lexer_error(char *line)
{
	(void)line;
	printf("minishell: syntax error near unexpected token `newline'\n");
	//free(line);
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
