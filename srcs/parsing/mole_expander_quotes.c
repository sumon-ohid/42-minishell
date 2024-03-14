/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_expander_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:52:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/14 22:25:02 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(int i, char *str, t_data *node, char mode)
{
	int	quotes;

	quotes = 0;
	node->quote = 0;
	while (str[i] && delim_type(str[i], node) != SPC)
	{
		if (delim_type(str[i], node) == QUOTE)
		{
			node->quote = str[i];
			if (mode == 'S')
			{
				if (str[i] == '\'')
					quotes++;
			}
			else
				quotes++;
		}
		i++;
	}
	return (quotes);
}

void	skip_till_quote(t_data *node, char *str, int *i, int *index)
{
	while (delim_type(str[*i], node) != QUOTE && str[*i])
	{
		if (str[*i] == '$')
			*i = *i + adjust_for_env(index, *i, str, node);
		else
		{
			(*i)++;
			(*index)++;
		}
	}
}

void	skip_in_squote(t_data *node, char *str, int *i, int *index)
{
	while (delim_type(str[*i], node) != QUOTE && str[*i])
	{
		(*i)++;
		(*index)++;
	}
}

// int	find_end_index(t_data *node, char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (delim_type(str[i], node) != SPC && str[i])
// 		i++;
// 	return (i);
// }

int	check_for_only_dollars(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] == '$')
	{
		i++;
		count++;
	}
	if (!str[i] || str[i] == ' ' || str[i] == '\n' || str[i] == '\"'
		|| str[i] == '\'' || str[i] == '-' || str[i] == '.')
	{
		return (count);
	}
	else
		return (0);
}
