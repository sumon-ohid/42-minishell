/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:54:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/14 18:02:42 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	survey(const char *str)
{
	int	c;
	int	minus_ctr;

	c = 0;
	minus_ctr = 0;
	while ((str[c] > 8 && str[c] < 14) || str[c] == 32)
		c++;
	if (str[c] == 43 || str[c] == 45)
	{
		if (str[c] == 45)
			minus_ctr++;
		c++;
	}
	if (minus_ctr % 2 == 0)
		return (c);
	else
		return (c * -1);
}

int	ft_atoll(const char *str)
{
	long long int	nb;
	int				sign;
	int				start;

	nb = 0;
	sign = survey(str);
	start = sign;
	if (sign < 0)
		start = sign * -1;
	while (str[start] > 47 && str[start] < 58)
	{
		nb = (nb * 10) + str[start] - '0';
		start++;
	}
	if (sign < 0)
		return (nb * -1);
	return (nb);
}

int	check_atoll(char *str)
{
	char	*num;
	char	*old;
	int		i;

	i = 0;
	old = str;
	num = "9223372036854775807";
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 19)
		return (0);
	if (ft_strlen(str) < 19)
		return (1);
	while (*str == num[i] && *str)
	{
		i++;
		str++;
	}
	if (!(*str) || *str < num[i])
		return (1);
	if (old[0] == '-' && i == 18 && *str == '8')
		return (1);
	return (0);
}
