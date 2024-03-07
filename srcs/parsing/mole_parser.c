/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/07 16:03:23 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdbool.h"

void    parse_error(t_data *node)
{
    ft_free_array(node->envp);
    free(node->tokens);
    free(node->input_line);
    handle_error("mole parser failed", -1);
    //exit(1);
}

/*int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter])
		counter++;
	return (counter);
}*/

char	*ft_substr_clean(char const *s, unsigned int start, size_t len, t_data *node)
{
	unsigned int	counter;
	char			*sub_str;

	counter = start;
	if (start >= ((unsigned int)ft_strlen(s)))
		return (NULL);
	while (s[counter])
		counter++;
	if ((counter - start) < len)
		sub_str = (char *)malloc(sizeof(char) * ((counter - start) + 1));
	else
		sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		parse_error(node);
	counter = 0;
	while (len && s[start])
	{
		sub_str[counter++] = s[start++];
		len--;
	}
	sub_str[counter] = '\0';
	return (sub_str);
}

int    is_delim(char c, t_data *node)
{
    char quote;
    
    quote = node->quote;
    node->parse_flag = 0;
    if (c == ' ' && !quote)
        return (1);
    else if (c == '\t' && !quote)
        return (1);
    else if (c == '\n' && !quote)
        return (1);
    else if (c == '\0')
        return (1);
    else if (c == '|' && !quote)
        return (2);
    else if (c == '<' && !quote)
        return (1);
    else if (c == '>' && !quote)
        return (1);
    else if (c == '\"' && quote != '\'')
        return (1);
    else if (c == '\'' && quote != '\"')
        return (1);
    else
        return (false);
}

int save_nulltoken(int end, t_data *node, t_token ***origin, int proc)
{
    char *str;

    str = node->input_line;
    if ((str[end] == '\"' && str[end + 1] == '\"')
        || (str[end] == '\'' && str[end + 1] == '\''))
    {
        node->parse_flag = 1;
        create_and_link_token(origin, proc, "", node);
        return (end + 2);
    }
    return (end);
}

int    parse_redirection(int end, t_data *node, t_token ***origin, int proc)
{
    char *str;

    str = node->input_line;
    if (str[end] == '\0')
        return (end);
    if ((str[end] == '>' && str[end + 1] == '>')
        || (str[end] == '<' && str[end + 1] == '<'))
    {
        create_and_link_token(origin, proc,
            ft_substr_clean(str, end, 2, node), node);
        return (end + 2);
    }
    else if (str[end] == '<' || str[end] == '>')
    {
        create_and_link_token(origin, proc,
            ft_substr_clean(str, end, 1, node), node);
        return (end + 1);
    }
    else if (str[end] == '|')
    {
        node->parse_flag = 1;
        return (end + 1);
    }
    return (save_nulltoken(end, node, origin, proc));
}

void    init_values(int *start, int *end, int *proc, t_data *node)
{
    *start = 0;
    *end = 0;
    node->quote = 0;
    node->parse_flag = 0;
    *proc = 0;
}

void    mole_parser(t_token ***origin, char *input, t_data *node)
{
    int     start;
    int     end;
    int     proc;
    
    init_values(&start, &end, &proc, node);
    while (input[end])
    {
        while (is_delim(input[end], node) == 1 && input[end])
            end++;
        if (!input[end])
            return ;
        start = end;
        while (!is_delim(input[end], node) && input[end])
            end++;
        if (input[end] == '|')
            proc++;
        end = parse_redirection(end, node, origin, proc);
        if (!node->parse_flag)
            create_and_link_token(origin, proc,
                ft_substr_clean(input, start, (end - start), node), node);
        if ((input[end] == '\"' || input[end] == '\'') && !(node->quote))
            node->quote = input[end++];
        else
            node->quote = 0;
        //printf("input[end] is now: %c\n", input[end]);
        //sleep(2);
    }
}
//printf("%s\n", ft_substr_clean(input, start, (end - start), node));
/*while (!is_delim(input[end], quote))
    end++;
printf("%s\n", ft_substr_clean(input, start, (end - start), node));*/
//
/*
int main(int argc, char **argv)
{
    t_token ***origin = NULL;
    t_data *node = NULL;
    
    if (argc != 2)
        return (0);
    mole_parser(origin, argv[1], node);
}*/