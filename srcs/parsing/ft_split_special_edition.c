/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special_edition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:27:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/08 13:14:42 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static size_t	word_counter(char const *s, char c)
{
	size_t	i;
	size_t	words;
	char	quote;

	i = 0;
	words = 0;
	if (!s)
		exit (1);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	printf("WORD NUMBER IS: %ld\n", words);
	return (words);
}*/

static size_t word_counter(char const *s, char c)
{
    size_t i = 0;
    size_t words = 0;
    char quote_char = 0;

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

static void	split_helper_pipes(char *s, char c, size_t *i, char *output)
{
	char	quote;
	int		flag;
	int		k;

	quote = 0;
	flag = 0;
	k = 0;
	while (s[*i] && (s[*i] != c || quote))
	{
		if (!flag && (s[*i] == '\'' || s[*i] == '\"'))
		{
			quote = s[*i];
			flag = 1;
		}
		else if (flag && (s[*i] == quote))
		{
			flag = 0;
			quote = 0;
		}
		output[k++] = s[(*i)++];
	}
	output[k] = '\0';
}

static void	split_helper(char *s, char c, size_t *i, char *output)
{
	char	quote;
	int		flag;
	int		k;

	quote = 0;
	flag = 0;
	k = 0;
	while (s[*i] && (s[*i] != c || quote))
	{
		if (!flag && (s[*i] == '\'' || s[*i] == '\"'))
		{
			quote = s[*i];
			flag = 1;
			*i = *i + 1;
		}
		else if (flag && (s[*i] == quote))
		{
			flag = 0;
			quote = 0;
			*i = *i + 1;
		}
		else
			output[k++] = s[(*i)++];
	}
	output[k] = '\0';
}

static int	l_count(char const *s, int i, char c)
{
	int	l;
	int	in_quotes;
	int	quote_num;

	l = i;
	in_quotes = 0;
	while (s[l] && (s[l] != c || in_quotes))
	{
		if ((s[l] == '\'' || s[l] == '\"') && !in_quotes)
			in_quotes = 1;
		else if ((s[l] == '\'' || s[l] == '\"') && in_quotes)
			in_quotes = 0;
		if (s[l] == '\'' || s[l] == '\"')
			quote_num++;
		l++;
	}
	return (l - quote_num);
}

char	**ft_split_special(char *s, char c, char mode, size_t j)
{
	char	**s_split;
	size_t	k;
	size_t	i;

	i = 0;
	s_split = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (s_split == NULL)
		handle_error("malloc in split failed", -1);
	while (s[i] && j < (word_counter(s, c)))
	{
		while (s[i] == c)
			i++;
		k = l_count(s, i, c);
		s_split[j] = (char *)malloc(sizeof(char) * (k - i + 1));
		if (!s_split[j])
			handle_error("malloc in split failed", -1); //return (ft_free_str(s_split, j));
		if (mode == 'P')
			split_helper_pipes(s, c, &i, s_split[j]);
		else
			split_helper(s, c, &i, s_split[j]);
		j++;
	}
	s_split[j] = NULL;
	return (s_split);
}
/*
char	**ft_split_special(char *s, char c, size_t i, size_t j)
{
	char	**s_split;
	size_t	k;
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	s_split = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (s_split == NULL)
		handle_error("malloc in split failed", -1);
	while (s[i])
	{
		if (s[i] != c)
		{
			k = k_count(s, i, c);
			s_split[j] = (char *)malloc(sizeof(char) * (k - i + 1));
			if (!s_split[j])
				handle_error("malloc in split failed", -1);//return (ft_free_str(s_split, j));
			k = 0;
			while (s[i] && (s[i] != c || quote))
			{
				if (!flag && (s[i] == '\'' || s[i] == '\"'))
				{
					quote = s[i];
					flag = 1;
					i++;
				}
				else if (flag && (s[i] == quote))
				{
					flag = 0;
					quote = 0;
					i++;
				}
				else
					s_split[j][k++] = s[i++];
			}
			s_split[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	s_split[j] = NULL;
	return (s_split);
}*/
