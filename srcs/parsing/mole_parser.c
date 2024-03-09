/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/09 15:48:55 by mhuszar          ###   ########.fr       */
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

int    delim_type(char c, t_data *node)
{
    node->parse_flag = 0;
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
    else if (c == '$')
        return (6);
    else
        return (0);
}

bool is_breaker(char c, t_data *node)
{
    if (delim_type(c, node) >= 1 && delim_type(c, node) <= 4)
        return (true):
    else
        return (false);
}

void skip(char *str, int *cur, char mode, t_data *node)
{
    if (mode == 'S')
    {
        while (delim_type(str[*cur], node) == SPC)
            *cur++;
    }
    else if (mode == 'C')
    {
        while (delim_type(str[*cur], node) == NONE)
            *cur++;
    } 
}

//void    test_waters()

int save_nulltoken(int end, t_data *node, t_token ***origin, int proc)
{
    char *str;

    str = node->input_line;
    if (str[end + 2] != '\0' && delim_type(str[end + 2], node) != SPC)
        return (0);
    else if ((str[end] == '\"' && str[end + 1] == '\"')
        || (str[end] == '\'' && str[end + 1] == '\''))
    {
        node->parse_flag = 1;
        create_and_link_token(origin, proc, "", node);
        return (1);
    }
    return (0);
}

int    create_breakertoken(int end, t_data *node, t_token ***origin, int proc)
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
        node->processes += 1;
        node->parse_flag = 1;
        return (end + 1);
    }
    return (end);//(save_nulltoken(end, node, origin, proc));
}

void    init_values(int *end, t_data *node)
{
    *end = 0;
    node->quote = 0;
    node->parse_flag = 0;
    node->processes = 0;
}

//SKIP SPC ONLY - MARK SPOT
//SKIP CHARS WHILE NOT *ANY* DELIM
//IF DELIM IS *BREAKER* : SPC, NULL, REDIR OR PIPE : CREATE TOKEN
//(IF WE SEE EMPTY STRING, CREATE EMPTY TOKEN)
//IF DELIM IS NOT BREAKER : QUOTE OR DOLLAR : CREATE STR BUT DONT TOKENIZE YET
//KEEP DOING THIS AND APPEND PIECES UNTIL NEXT BREAKER, THEN TOKENIZE - QUOTE STATUS IS ALWAYS TRUE!!
//WE ONLY REACH THIS PART IF WE HAVE CREATED 0 OR 1 TOKEN AND STAND AT 1 BREAKER
//CREATE BREAKER TOKENS IF ANY - << OR < ETC
//WE HAVE ONLY REACHED THIS PART IF CREATED AT LEAST ONE TOKEN
//GO BACK TO BEGINNING
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
            detach_tokens(&end, origin, node, *start);
    }
        
    start = end;
    end = skip(input, end, 'C', node);
    
}

void    detach_tokens(int *end, t_token ***origin, t_data *node, int *start)
{
    char    *str;
    size_t  size_left;

    str = node->input_line;
    chars_left = (ft_strlen(str) - *end) - 1;
    if (is_breaker(str[*end]))
    {
        *end = create_breakertoken(*end, node, origin, node->processes);
        return ;
    }
    else if (chars_left >= 2 && delim_type(str[*end], node) == QUOTE)
    {
        if (save_nulltoken(*end, node, origin, node->processes))
            return ;
    }
    expand_append(origin, node, end);
}

void    expand_append(t_token ***origin, t_data *node, int *end)
{
    
}

/*void    mole_parser(t_token ***origin, char *input, t_data *node)
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
}*/
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