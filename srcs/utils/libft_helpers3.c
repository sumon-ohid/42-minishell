/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:43:23 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 18:55:38 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_quote_detector(char *big, char *little)
{
	size_t	counter_a;
	size_t	counter_b;

	counter_a = 0;
	counter_b = 0;
	if (!little || !big)
		return (NULL);
	while (big[counter_a] != 0 && little[counter_b] != 0)
	{
		while (big[counter_a] == little[counter_b])
		{
			counter_a++;
			counter_b++;
			if (little[counter_b] == '\0')
				return (&big[counter_a]);
		}
		counter_a = (counter_a - counter_b) + 1;
		counter_b = 0;
	}
	return (NULL);
}
