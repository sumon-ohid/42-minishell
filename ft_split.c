/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 07:40:56 by sumon             #+#    #+#             */
/*   Updated: 2024/01/04 13:00:22 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_counter(char const *s, char c)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			x++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (x);
}

char	**ft_free_str(char **str, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	k_count(char const *s, int i, char c)
{
	int	k;

	k = i;
	while (s[k] && s[k] != c)
		k++;
	return (k);
}

char	**ft_split(char const *s, char c, size_t i, size_t j)
{
	char	**s_split;
	size_t	k;

	s_split = (char **)malloc(sizeof(char *) * (ft_counter(s, c) + 1));
	if (s_split == NULL)
		return (NULL);
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
