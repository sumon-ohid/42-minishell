/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_breakertokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:06:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/11 21:55:19 by msumon           ###   ########.fr       */
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

	str = node->input_line;
	if (str[end + 2] != '\0' && delim_type(str[end + 2], node) != SPC)
		return (0);
	else if ((str[end] == '\"' && str[end + 1] == '\"') || (str[end] == '\''
			&& str[end + 1] == '\''))
	{
		create_and_link_token(origin, proc, "", node);
		return (1);
	}
	return (0);
}

void	breakermaker(int proc, int end, t_data *node, int num)
{
	char	*result;

	result = ft_substr_clean(node->input_line, end, num, node);
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
