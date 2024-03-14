/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:05:17 by msumon            #+#    #+#             */
/*   Updated: 2024/03/14 22:34:04 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	adjust_for_env(int *count, int i, char *str, t_data *node)
{
	char	tmp[2048];
	int		c;
	int		len;
	int		flag;

	flag = check_for_only_dollars(str, i);
	c = 0;
	if (flag)
	{
		*count = *count + flag;
		return (flag);
	}
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\n'
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '-' && str[i] != '.'
		&& c < 2045)
	{
		tmp[c++] = str[i++];
	}
	tmp[c] = '\0';
	len = ft_strlen(ft_getenv(tmp, node));
	*count = *count + len;
	return (c + 1);
}

void	handle_without_zones(t_data *node, t_token ***origin, char *res)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (res[i])
	{
		skip(res, &i, 'S', node);
		j = i;
		skip(res, &i, 'X', node);
		word = ft_substr(res, j, i - j);
		if (!word)
		{
			free(res);
			parse_error(node, 1, "malloc in zone handler failed", -1);
		}
		create_and_link_token(origin, node->processes, word, node);
		free(word);
	}
}

void	init_creator(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

void	creator_loop(t_data *node, char *res, int **zones, char *str)
{
	int		i;
	int		j;
	char	*word;
	int		max;

	max = count_quotes(0, str, node, 'A') / 2;
	i = 0;
	j = 0;
	while (res[i])
	{
		while (res[i] == ' ' && !inside_zone(zones, max, i))
			i++;
		j = i;
		while (res[i] && (res[i] != ' ' || inside_zone(zones, max, i)))
			i++;
		word = ft_substr(res, j, i - j);
		if (!word)
		{
			free_zone(zones, max);
			free(res);
			parse_error(node, 1, "malloc in expansion split failed", -1);
		}
		create_and_link_token(&(node->tokens), node->processes, word, node);
		free(word);
	}
}

void	sever_into_tokens(t_token ***origin, t_data *node, int start, char *res)
{
	char	*str;
	int		**zones;

	str = node->input_line + start;
	zones = create_zones(node, str, res);
	if (!zones)
		return (handle_without_zones(node, origin, res));
	creator_loop(node, res, zones, str);
	free_zone(zones, (count_quotes(0, str, node, 'A') / 2));
}

// void	sever_into_tokens(t_token ***origin, t_data *node, int start, char *res)
// {
// 	char 	*str;
// 	int		**zones;
// 	int		i;
// 	int		j;
// 	char	*word;
// 	bool	action_flag;
//
// 	node->end_index = 0;
// 	str = node->input_line + start;
// 	zones = create_zones(node, str);
// 	if (!zones)
// 		return (handle_without_zones(node, origin, res));
// 	while (node->end_index >= i && res[i])
// 	{
// 		node->quote = 0;
// 		skip(res, &i, 'S', node);
// 		if (action_flag)
// 			j = i;
// 		skip(res, &i, 'X', node);
// 		if (!res[i] || !inside_zone(zones,
//			(count_quotes(0, str, node, 'A') / 2), i))
// 		{
// 			action_flag = true;
// 			word = ft_substr(res, j, i - j);
// 			if (!word)
// 				parse_error(node, 1, "malloc in expansion split failed", -1);
// 			create_and_link_token(origin, node->processes, word, node);
// 			free(word);
// 		}
// 		else
// 			action_flag = false;
// 	}
// 	free_zone(zones, (count_quotes(0, str, node, 'A') / 2));
// }

// void	creator_loop(t_data *node, char *res, int **zones, char *str)
// {
// 	int		i;
// 	int		j;
// 	bool	action_flag;
// 	char	*word;
// 	int		max;

// 	max = count_quotes(0, str, node, 'A') / 2;
// 	printf("res is:%sH\n", res);
// 	init_creator(&i, &j, &action_flag);
// 	while (node->end_index >= i && res[i])
// 	{
// 		node->quote = 0;
// 		skip(res, &i, 'S', node);
// 		if (action_flag)
// 			j = i;
// 		skip(res, &i, 'X', node);
// 		if (!res[i] || !inside_zone(zones, max, i))
// 		{
// 			action_flag = true;
// 			if (i - j == 0)
// 				return ;
// 			printf("zone range is: %d - %d", zones[0][0], zones[0][1]);
// 			word = ft_substr(res, j, i - j);
// 			if (!word)
// 			{
// 				free_zone(zones, max);
// 				free(res);
// 				parse_error(node, 1, "malloc in expansion split failed", -1);
// 			}
// 			create_and_link_token(&(node->tokens), node->processes, word, node);
// 			free(word);
// 		}
// 		else
// 			action_flag = false;
// 	}
// }
