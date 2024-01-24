/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:02:15 by msumon            #+#    #+#             */
/*   Updated: 2024/01/24 20:40:37 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**ft_malloc(int size, char **str)
{
	char	**str2;
	int		i;

	i = 0;
	str2 = malloc(sizeof(char *) * (size + 1));
	if (!str2)
		return (NULL);
	while (i < size)
	{
		str2[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		i++;
	}
	return (str);
}
