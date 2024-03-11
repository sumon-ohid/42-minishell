/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special_edition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:27:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/06 16:34:14 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	word_counter(char const *s, char c, int i, char quote_char)
{
	size_t	words;

	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] && s[i] != c)
		{
			if ((s[i] == '\'' || s[i] == '\"') && !quote_char)
			{
				quote_char = s[i++];
				while (s[i] != quote_char && s[i] != '\0')
					i++;
				quote_char = 0;
				i++;
			}
			else
				i++;
		}
	}
	return (words);
}

static void	process_quotes(char *s, size_t *i, char *output, t_split *data)
{
	data->quote = s[*i];
	data->flag = 1;
	(*i)++;
	data->only_spaces = 1;
	while (s[*i] && s[*i] != data->quote)
	{
		if (s[*i] != ' ')
		{
			data->only_spaces = 0;
			break ;
		}
		(*i)++;
	}
	if (data->only_spaces && s[*i] == data->quote)
	{
		while (s[*i + 1] == ' ')
			(*i)++;
		if (s[*i + 1] == ' ' || s[*i + 1] == '\0')
		{
			output[data->k++] = data->quote;
			output[data->k++] = data->quote;
			*i = *i + 1;
		}
		 else if (s[*i + 1] != ' ' && s[*i + 1] != '\0')
        {
            output[data->k++] = s[*i + 1];
			while (s[*i + 1] != ' ' && s[*i + 1] != '\0')
				(*i)++;
        }
	}
}

static void	split_helper(char *s, char c, size_t *i, char *output)
{
	t_split	*data;

	data = malloc(sizeof(t_split));
	if (data == NULL)
		return ;
	data->quote = 0;
	data->flag = 0;
	data->k = 0;
	data->only_spaces = 0;
	while (s[*i] && (s[*i] != c || data->quote))
	{
		if (!data->flag && (s[*i] == '\'' || s[*i] == '\"'))
			process_quotes(s, i, output, data);
		else if (data->flag && (s[*i] == data->quote))
		{
			data->flag = 0;
			data->quote = 0;
			(*i)++;
		}
		else
			output[data->k++] = s[(*i)++];
	}
	output[data->k] = '\0';
	free(data);
}

static int	l_count(char const *s, int i, char c)
{
	int		k;
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	k = i;
	while (s[k] && (s[k] != c || quote))
	{
		if (!flag && (s[k] == '\'' || s[k] == '\"'))
		{
			quote = s[k];
			flag = 1;
			k++;
		}
		else if (flag && (s[k] == quote))
		{
			flag = 0;
			quote = 0;
			k++;
		}
		else
			k++;
	}
	return (k);
}

char	**ft_split_special(char *s, char c, char mode, size_t j)
{
	char	**s_split;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_split = malloc(sizeof(char *) * (word_counter(s, c, 0, 0) + 1));
	if (s_split == NULL)
		return (NULL);
	while (s[i] && j < (word_counter(s, c, 0, 0)))
	{
		while (s[i] == c)
			i++;
		s_split[j] = malloc(l_count(s, i, c) - i + 1);
		if (!s_split[j])
			return (NULL);
		if (mode == 'P')
			split_helper_pipes(s, c, &i, s_split[j]);
		else
			split_helper(s, c, &i, s_split[j]);
		j++;
	}
	s_split[j] = NULL;
	return (s_split);
}
