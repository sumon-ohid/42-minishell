/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:51:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/05 13:51:34 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	entry_check(t_data *node, char *line)
{
	char	**arr;
	t_token	**tokens;

	if (!ft_lexical_checker(line))
        return(1);
    tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	if (!tokens)
	{
		perror("Memory allocation failed");
		return (1);
	}
	arr = parse_input(line);
	if (!arr)
	{
		free(tokens);
		return (1);
	}
	process_words(&tokens, arr, line);
	executor_init(node, tokens, pipe_counter(line), line);
	//free_tokens(tokens);
	free(line);
	free_arr(arr);
	return (0);
}

int ft_lexical_checker(char *line)
{
    //we have to iterate through line and implement the following here:
    //1. check if a ' or " has started, they also have a maching sign that closes it
    //2. There are no two pipes following each other, like | | or || (we dont implement OR operator)
    //3. There are no two redirections following each other, like > > or < < or >> >> etc. (BUT >> is okay)
    //4. there is no pipe without anything following it, like ls | ls |
    //5. there is no redirection without anything following it, like ls | ls  >
    //6. there should not be any spaces sorrounding a = sign
    //7. of course all of the above is allowed to happen inside quotes ("like this" 'or this')
    //If any error of the above happens, display "Syntax error near unexpected token", free line, return 0
    //Otherwise: return 1
    return (1);
}