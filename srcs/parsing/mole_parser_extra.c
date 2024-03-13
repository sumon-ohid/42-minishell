/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:05:17 by msumon            #+#    #+#             */
/*   Updated: 2024/03/13 23:07:57 by mhuszar          ###   ########.fr       */
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
		//printf("round: %d, str[i] is: %c\n", i, str[i]);
		if (delim_type(str[i], node) == QUOTE)
		{
			node->quote = str[i];
			if (mode == 'S')
			{
				if (str[i] == '\'')
					quotes++;
			}
			else
			{
				//printf("found: %c, incremented\n", str[i]);
				quotes++;
			}
		}
		i++;
	}
	//printf("result is: %d\n", quotes);
	return (quotes);
}

int	find_end_index(t_data *node, char *str)
{
	int i;

	i = 0;
	while (delim_type(str[i], node) != SPC && str[i])
		i++;
	return (i);
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

int	adjust_for_env(int *count, int i, char *str, t_data *node)
{
	char tmp[2048];
	int c;
	int len;

	//tmp[0] = str[i];
	c = 0;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\n'
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '-'
			&& str[i] != '.' && c < 2045)
	{
		tmp[c++] = str[i++];
	}
	tmp[c] = '\0';
	len = ft_strlen(ft_getenv(tmp, node));
	//printf("tmp is: %s, env is: %s, length of expanded str is: %d\n", tmp, ft_getenv(tmp, node), len);
	*count = *count - c + len;
	//printf("count val is %d, c val is: %d\n", *count, c);
	return (c);
}

void skip_till_quote(t_data *node, char *str, int *i, int *index)
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

void skip_in_quote(t_data *node, char *str, int *i, int *index)
{
	while (delim_type(str[*i], node) != QUOTE && str[*i])
	{
			(*i)++;
			(*index)++;
	}
}

int	**fill_zones(t_data *node, char *str, int max, int **zones)
{
	int		counter;
	int		subtract;
	int		start;
	int		index;

	start = 0;
	subtract = 0;
	index = 0;
	counter = 0;
	//printf("value of max is: %d\n", max);
	while (counter < max)
	{
		node->quote = 0;
		skip_till_quote(node, str, &start, &index);
		//printf("we are at %c, index is %d\n", str[start], index);
		zones[counter][0] = index - subtract;
		subtract++;
		start++;
		index++;
		//printf("we are at %c, index is %d\n", str[start], index);
		if (str[start - 1] == '\'')
			skip_in_quote(node, str, &start, &index);
		else
			skip_till_quote(node, str, &start, &index);
		//printf("we are at %c, index is %d\n", str[start], index);
		zones[counter][1] = index - subtract;
		subtract++;
		counter++;
	}
	index = index - count_quotes(0, str, node, 'A');
	node->end_index = index;
	//printf("end index set to: %d\n", index);
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
		parse_error(node, 1, "malloc in parsing failed", -1);
	max = quote_num;
	while (quote_num)
	{
		zones[quote_num - 1] = malloc(sizeof(int) * 2);
		if (!zones[quote_num - 1])
			parse_error(node, 1, "malloc in parsing failed", -1);
		quote_num--;
	}
	return (fill_zones(node, str, max, zones));
}

void	handle_without_zones(t_data *node, t_token ***origin, char *res)
{
	int i;
	int j;
	char *word;

	i = 0;
	j = 0;
	while (res[i])
	{
		skip(res, &i, 'S', node);
		j = i;
		skip(res, &i, 'X', node);
		word = ft_substr(res, j, i - j);
		if (!word)
			parse_error(node, 1, "malloc in parsing failed", -1);
		//printf("the new word is: %s\n", word);
		create_and_link_token(origin, node->processes, word, node);
		free(word);
	}
}

void	free_zone(int **zone, int max)
{
	int counter;

	counter = 0;
	while (counter < max)
	{
		free(zone[counter]);
		counter++;
	}
	free(zone);
}

void	sever_into_tokens(t_token ***origin, t_data *node, int start, char *res)
{
	char 	*str;
	int		**zones;
	int		i;
	int		j;
	char	*word;
	bool	action_flag;
	
	//printf("entering function\n");
	i = 0;
	j = 0;
	action_flag = true;
	node->end_index = 0;
	str = node->input_line + start;
	zones = create_zones(node, str);
	if (!zones)
		return (handle_without_zones(node, origin, res));
	while (node->end_index >= i && res[i])
	{
		node->quote = 0;
		skip(res, &i, 'S', node);
		if (action_flag)
			j = i;
		skip(res, &i, 'X', node);
		//printf("we have arrived at: %c, ", res[i]);
		if (!res[i] || !inside_zone(zones, (count_quotes(0, str, node, 'A') / 2), i))
		{
			action_flag = true;
			word = ft_substr(res, j, i - j);
			if (!word)
				parse_error(node, 1, "malloc in parsing failed", -1);
			//printf("the new word is: %s\n", word);
			create_and_link_token(origin, node->processes, word, node);
			free(word);
		}
		else
			action_flag = false;
	}
	//printf("loop broken: last char is: %c, previous: %c\n", res[i], res[i - 1]);
	//printf("quote counter result: %d\n", count_quotes(0, res, node, 'A'));
	free_zone(zones, (count_quotes(0, str, node, 'A') / 2));
}
