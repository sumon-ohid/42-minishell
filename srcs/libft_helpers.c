/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:31:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/12 12:22:35 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strstr(const char *big, const char *little)
{
	size_t	counter_a;
	size_t	counter_b;

	counter_a = 0;
	counter_b = 0;
	if (!little)
		return (0);
	while (big[counter_a] != 0 && little[counter_b] != 0)
	{
		while (big[counter_a] == little[counter_b])
		{
			counter_a++;
			counter_b++;
			if (little[counter_b] == '\0')
				return (1);
		}
		counter_a = (counter_a - counter_b) + 1;
		counter_b = 0;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, int save_flag)
{
	int		ctr1;
	int		ctr2;
	char	*new_str;

	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (0);
	ctr1 = 0;
	ctr2 = 0;
	while (s1[ctr1])
	{
		new_str[ctr1] = s1[ctr1];
		ctr1++;
	}
	while (s2[ctr2])
		new_str[ctr1++] = s2[ctr2++];
	new_str[ctr1] = '\0';
	if (save_flag)
		free(s1);
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
		return (0);
	counter = 0;
	while (len && s[start])
	{
		sub_str[counter++] = s[start++];
		len--;
	}
	sub_str[counter] = '\0';
	return (sub_str);
}

int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter])
		counter++;
	return (counter);
}

char	*ft_strdup(const char *src)
{
	int		counter;
	int		counter2;
	char	*ptr;

	counter = 0;
	counter2 = 0;
	while (src[counter])
		counter++;
	ptr = (char *)malloc(counter + 1);
	if (!ptr)
		return (0);
	while (counter2 < counter)
	{
		ptr[counter2] = src[counter2];
		counter2++;
	}
	ptr[counter2] = '\0';
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}