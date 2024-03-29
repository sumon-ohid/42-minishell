/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_breakertokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:06:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/13 22:14:21 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_breaker(char c, t_data *node)
{
	if (delim_type(c, node) >= 1 && delim_type(c, node) <= 4)
		return (true);
	else
		return (false);
}

int	saved_nulltoken(int end, t_data *node, t_token ***origin, int proc)
{
	char	*str;
	char	*empty;

	str = node->input_line;
	if (str[end + 2] != '\0' && delim_type(str[end + 2], node) != SPC)
		return (0);
	else if ((str[end] == '\"' && str[end + 1] == '\"') || (str[end] == '\''
			&& str[end + 1] == '\''))
	{
		empty = ft_strdup("");
		if (!empty)
			parse_error(node, 1, "malloc failed at parser", -1);
		create_and_link_token(origin, proc, empty, node);
		free(empty);
		return (1);
	}
	return (0);
}

void	breakermaker(int proc, int end, t_data *node, int num)
{
	char	*result;

	result = ft_substr_clean(node->input_line, end, num, node);
	if (ft_strcmp(result, "<<") == 0)
		node->delim_turn = true;
	create_and_link_token(&(node->tokens), proc, result, node);
	free(result);
}

int	create_breakertoken(int end, t_data *node, int proc)
{
	char	*str;

	str = node->input_line;
	if (str[end] == '\0')
		return (end);
	if ((str[end] == '>' && str[end + 1] == '>') || (str[end] == '<' && str[end
				+ 1] == '<') || (str[end] == '>' && str[end + 1] == '|'))
	{
		breakermaker(proc, end, node, 2);
		return (end + 2);
	}
	else if (str[end] == '<' || str[end] == '>')
	{
		breakermaker(proc, end, node, 1);
		return (end + 1);
	}
	else if (str[end] == '|')
	{
		node->command_flag = 0;
		node->processes += 1;
		return (end + 1);
	}
	return (end);
}

void	create_delim_token(int *end, t_data *node, t_token ***origin)
{
	int		counter;
	char	*delim;
	char	*str;
	char	temp[4096];

	counter = 0;
	str = node->input_line;
	while (delim_type(str[*end], node) != SPC && str[*end] && counter < 4093)
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
