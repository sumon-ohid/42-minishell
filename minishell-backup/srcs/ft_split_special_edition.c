/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special_edition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:27:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/05 14:27:34 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

static size_t	word_counter(char const *s, char c)
{
	size_t	i;
	size_t	words;
    int     inside_quote;

	i = 0;
	words = 0;
    inside_quote = 0;
	if (!s)
		return (0);
	while (s[i])
	{
        while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words++;
        if (s[i] == '\'' || s[i] == '\"')
        {
            i++;
            while (s[i] && !(s[i] == '\'' || s[i] == '\"'))
                i++;
        }
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c, size_t i, size_t j)
{
	char	**s_split;
	size_t	k;

	s_split = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (s_split == NULL)
		return (NULL);
	if (!s)
		return (s_split);
	while (s[i])
	{
		if (s[i] != c)
		{
			k = k_count(s, i, c);
			s_split[j] = (char *)malloc(sizeof(char) * (k - i + 1));
			if (!s_split[j])
				return (ft_free_str(s_split, j));
			k = 0;
			while (s[i] && s[i] != c)
				s_split[j][k++] = s[i++];
			s_split[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	s_split[j] = NULL;
	return (s_split);
}

char    **ft_split_special(char *str)
{

}