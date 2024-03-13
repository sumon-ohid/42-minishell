/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:05:17 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 18:13:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(int i, char *str, t_data *node)
{
	int	quotes;
	
	quotes = 0;
	while (str[i] && delim_type(str[i], node) != SPC)
	{
		if (delim_type(str[i], node) == QUOTE)
			quotes++;
		i++;
	}
	return (quotes);
}

bool	inside_zone(int **zones, int total, int cur)
{
	int	c;

	c = 0;
	while (c < total)
	{
		if (cur >= zones[c][0] && cur <= zones[c][1])
			return (true);
		c++;
	}
	return (false);
}

int	**fill_zones(t_data *node, int start, int max)
{
	
}

int	**create_zones(t_data *node, int start)
{
	int		quote_num;
	int		**zones;
	int		max;

	quote_num = count_quotes(start, node->input_line, node) / 2;
	zones = malloc(sizeof(int *) * quote_num);
	if (!zones)
		parse_error(node, 1, "malloc in parsing failed", -1);
	max = quote_num;
	while (quote_num)
	{
		zones[quote_num - 1] = malloc(sizeof(int) * 2);
		if (!zones[quote_num - 1])
			parse_error(node, 1, "malloc in parsing failed", -1);
		quote_num--;
	}
	return (fill_zones(node, start, max));
}

void	sever_into_tokens(t_token ***origin, t_data *node, int start, char *res)
{
	char 	*str;
	
	
}
