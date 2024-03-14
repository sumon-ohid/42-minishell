/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_expander_zones.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:54:22 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/14 19:19:32 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	init_zone_vars(int *start, int *sub, int *index, int *count)
{
	*start = 0;
	*sub = 0;
	*index = 0;
	*count = 0;
}

int	**fill_zones(t_data *node, char *str, int max, int **zones)
{
	int		counter;
	int		subtract;
	int		start;
	int		index;

	init_zone_vars(&start, &subtract, &index, &counter);
	while (counter < max)
	{
		node->quote = 0;
		skip_till_quote(node, str, &start, &index);
		zones[counter][0] = index - subtract;
		node->quote = str[start];
		subtract++;
		start++;
		if (node->quote == '\'')
			skip_in_squote(node, str, &start, &index);
		else
			skip_till_quote(node, str, &start, &index);
		zones[counter][1] = index - subtract;
		subtract++;
		start++;
		counter++;
	}
	node->end_index = index;
	return (zones);
}

int	**create_zones(t_data *node, char *str)
{
	int		quote_num;
	int		**zones;
	int		max;

	quote_num = count_quotes(0, str, node, 'A') / 2;
	if (quote_num == 0)
		return (NULL);
	zones = malloc(sizeof(int *) * quote_num);
	if (!zones)
		parse_error(node, 1, "malloc in zone creator failed", -1);
	max = quote_num;
	while (quote_num)
	{
		zones[quote_num - 1] = malloc(sizeof(int) * 2);
		if (!zones[quote_num - 1])
			parse_error(node, 1, "malloc in zone creator failed", -1);
		quote_num--;
	}
	return (fill_zones(node, str, max, zones));
}

void	free_zone(int **zone, int max)
{
	int	counter;

	counter = 0;
	while (counter < max)
	{
		free(zone[counter]);
		counter++;
	}
	free(zone);
}
