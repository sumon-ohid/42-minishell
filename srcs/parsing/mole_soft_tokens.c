/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_soft_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:05:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/11 21:47:24 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_append(t_data *node, int *end)
{
	int		start;
	char	*str;
	char	*result;

	node->elements = NULL;
	str = node->input_line;
	while (str[*end] && !is_breaker(str[*end], node))
	{
		if (delim_type(str[*end], node) == QUOTE && !node->quote)
			node->quote = str[(*end)++];
		start = *end;
		if (!node->quote)
			(*end)++;
		while (!delim_type(str[*end], node))
			(*end)++;
		create_element(&(node->elements), node, start, *end);
		if (node->quote && delim_type(str[*end], node) == QUOTE)
			(*end)++;
		node->quote = 0;
	}
	result = concatenate_elements(node->elements, node);
	free_elements(node->elements);
	node->elements = NULL;
	return (result);
}

void	create_element(t_element **elements, t_data *node, int start, int end)
{
	t_element	*new;
	char		*data;

	new = malloc(sizeof(t_element));
	if (!new)
		parse_error(node, 1, "error at create_element", -1);
	data = ft_substr(node->input_line, start, (end - start));
	new->exported = false;
	if (!data)
	{
		free(new);
		parse_error(node, 1, "error at create_element", -1);
	}
	if (ft_strstr(data, "$") && node->quote != '\'')
	{
		new->str = handle_envp(data, node);
		new->exported = true;
		free(data);
	}
	else
		new->str = data;
	new->next = NULL;
	ft_lstadd_back(elements, new);
}

char	*concatenate_elements(t_element *elements, t_data *node)
{
	char	*result;

	if (!elements || !elements->str)
		parse_error(node, 1, "something went wrong with elements", -1);
	if (elements->str[0] == ' ' && elements->exported == true)
		result = ft_strdup((elements->str) + 1);
	else
		result = ft_strdup(elements->str);
	if (!result)
		parse_error(node, 1, "strdup failed at parsing", -1);
	while (elements->next)
	{
		elements = elements->next;
		result = ft_strjoin(result, elements->str, 1);
		if (!result)
			parse_error(node, 1, "strjoin failed at parsing", -1);
	}
	return (result);
}

void	free_elements(t_element *elements)
{
	t_element	*cur;
	t_element	*prev;

	cur = elements;
	if (!cur)
		return ;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->str);
		free(prev);
	}
}
