/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/10 15:45:27 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdbool.h"

char	*ft_substr_clean(char const *s, unsigned int start, size_t len, t_data *node)
{
	unsigned int	counter;
	char			*sub_str;

	counter = start;
	if (start >= ((unsigned int)ft_strlen(s)))
		parse_error(node, 1, "substr failed at parsing", -1);
	while (s[counter])
		counter++;
	if ((counter - start) < len)
		sub_str = (char *)malloc(sizeof(char) * ((counter - start) + 1));
	else
		sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		parse_error(node, 1, "substr failed at parsing", -1);
	counter = 0;
	while (len && s[start])
	{
		sub_str[counter++] = s[start++];
		len--;
	}
	sub_str[counter] = '\0';
	return (sub_str);
}

int    delim_type(char c, t_data *node)
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
    else if (c == '$' && !(node->quote)) //not sure if this is a good idea
        return (6);
    else
        return (0);
}

bool is_breaker(char c, t_data *node)
{
    if (delim_type(c, node) >= 1 && delim_type(c, node) <= 4)
        return (true);
    else
        return (false);
}

void skip(char *str, int *cur, char mode, t_data *node)
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
}

int saved_nulltoken(int end, t_data *node, t_token ***origin, int proc)
{
    char *str;

    str = node->input_line;
    if (str[end + 2] != '\0' && delim_type(str[end + 2], node) != SPC)
        return (0);
    else if ((str[end] == '\"' && str[end + 1] == '\"')
        || (str[end] == '\'' && str[end + 1] == '\''))
    {
        create_and_link_token(origin, proc, "", node);
        return (1);
    }
    return (0);
}

void   breakermaker(int proc, int end, t_data *node, int num)
{
    char *result;

    result = ft_substr_clean(node->input_line, end, num, node);
    create_and_link_token(&(node->tokens), proc, result, node);
    free(result);
}

int    create_breakertoken(int end, t_data *node, int proc)
{
    char *str;

    str = node->input_line;
    if (str[end] == '\0')
        return (end);
    if ((str[end] == '>' && str[end + 1] == '>')
        || (str[end] == '<' && str[end + 1] == '<'))
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
        node->processes += 1;
        return (end + 1);
    }
    return (end);
}

void    init_values(int *end, t_data *node)
{
    *end = 0;
    node->quote = 0;
    node->processes = 0;
}

void    mole_parser(t_token ***origin, char *input, t_data *node)
{
    int     end;

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

void    detach_tokens(int *end, t_token ***origin, t_data *node)
{
    char    *str;
    size_t  chars_left;
    char    *result;

    str = node->input_line;
    chars_left = (ft_strlen(str) - *end) - 1;
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
    result = expand_append(node, end);
    node->quote = SINGLE_QUOTE;
    create_and_link_token(origin, node->processes, result, node);
    free(result);
}

char    *expand_append(t_data *node, int *end)
{
    int         start;
    char        *str;
    char        *result;

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

void create_element(t_element **elements, t_data *node, int start, int end)
{
    t_element *new;
    char *data;

    new = malloc(sizeof(t_element));
    if (!new)
        parse_error(node, 1, "error at create_element", -1);
    data = ft_substr(node->input_line, start, (end - start));
    if (!data)
    {
        free(new);
        parse_error(node, 1, "error at create_element", -1);
    }
    if (ft_strstr(data, "$") && node->quote != '\'')
    {
        new->str = handle_envp(data, node); //is this properly protected against malloc fails?
        free(data);
    }
    else
        new->str = data;
    new->next = NULL;
    ft_lstadd_back(elements, new);
}

char *concatenate_elements(t_element *elements, t_data *node)
{
    char *result;

    if (!elements)
        parse_error(node, 1, "something went wrong with elements", -1);
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

void free_elements(t_element *elements)
{
    t_element *cur;
    t_element *prev;

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
