/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/13 16:41:50 by mhuszar          ###   ########.fr       */
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

int	delim_type(char c, t_data *node)
{
	if (c == ' ' && !(node->quote))
		return (1);
	else if (c == '\t' && !(node->quote))
		return (1);
	else if (c == '\n' && !(node->quote))
		return (1);
	else if (c == '|' && !(node->quote))
		return (2);
	else if (c == '<' && !(node->quote))
		return (3);
	else if (c == '>' && !(node->quote))
		return (3);
	else if (c == '\0')
		return (4);
	else if (c == '\"' && node->quote != '\'')
		return (5);
	else if (c == '\'' && node->quote != '\"')
		return (5);
	else if (c == '$' && !(node->quote))
		return (6);
	else
		return (0);
}

void	skip(char *str, int *cur, char mode, t_data *node)
{
	if (mode == 'S')
	{
		while (delim_type(str[*cur], node) == SPC)
			(*cur)++;
	}
	else if (mode == 'C')
	{
		while (delim_type(str[*cur], node) == NONE)
			(*cur)++;
	}
	else if (mode == 'X')
	{
		while (delim_type(str[*cur], node) != SPC && str[*cur])
			(*cur)++;
	}
}

void	init_values(int *end, t_data *node)
{
	*end = 0;
	node->quote = 0;
	node->processes = 0;
}
