/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:05:17 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 16:05:55 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
