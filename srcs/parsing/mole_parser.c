/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/13 16:05:50 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mole_parser(t_token ***origin, char *input, t_data *node)
{
	int	end;

	init_values(&end, node);
	while (input[end])
	{
		skip(input, &end, 'S', node);
		if (!input[end])
			return ;
		else
			detach_tokens(&end, origin, node);
		node->quote = 0;
	}
}

void	create_soft_token(t_data *node, int *end, t_token ***origin)
{
	char	*result;

	result = expand_append(node, end);
	if (ft_strcmp(result, "") == 0)
	{
		free(result);
		return ;
	}
	node->quote = SINGLE_QUOTE;
	create_and_link_token(origin, node->processes, result, node);
	free(result);
}

void	create_delim_token(int *end, t_data *node, t_token ***origin)
{
	int		counter;
	char	*delim;
	char	*str;
	char	temp[2048];

	counter = 0;
	str = node->input_line;
	while (delim_type(str[*end], node) != SPC && str[*end] && counter < 2046)
	{
		if (delim_type(str[*end], node) == QUOTE)
			node->quote = str[*end];
		else
			temp[counter++] = str[*end];
		(*end)++;
	}
	temp[counter] = '\0';
	delim = ft_strdup(temp);
	if (!delim)
		parse_error(node, 1, "malloc error at parser", -1);
	create_and_link_token(origin, node->processes, delim, node);
	free(delim);
	node->delim_turn = false;
}

void	detach_tokens(int *end, t_token ***origin, t_data *node)
{
	char	*str;
	size_t	chars_left;

	str = node->input_line;
	chars_left = (ft_strlen(str) - *end);
	if (is_breaker(str[*end], node))
	{
		*end = create_breakertoken(*end, node, node->processes);
		return ;
	}
	else if (chars_left >= 2 && delim_type(str[*end], node) == QUOTE)
	{
		if (saved_nulltoken(*end, node, origin, node->processes))
		{
			*end += 2;
			return ;
		}
	}
	if (node->delim_turn)
	{
		create_delim_token(end, node, origin);
		return ;
	}
	create_soft_token(node, end, origin);
}
