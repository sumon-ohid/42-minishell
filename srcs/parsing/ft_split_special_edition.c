/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special_edition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:27:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/07 16:08:47 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (words);
}

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
}
