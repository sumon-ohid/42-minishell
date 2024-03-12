/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:54:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/12 20:18:21 by mhuszar          ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;
	int	start;

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
#include<stdint.h>

/*int	check_atoll(char *str)
{
	char 	*num;
	char 	*num2;
	int		i;
	
	
	if (ft_strlen(str) > 20 || (ft_strlen(str) > 19 str[0] != '-'))
		return (0);
	num = "9223372036854775807";
	num2 = "-9223372036854775808";
	i = 0;
	while (str[i] <= num[i] && str[i])
		i++;
	if (!str[i])
		return (1);
	i = 1;
	while (str[i] <= num2[i] && str[i])
		i++;
	
}*/
/*
#include<stdio.h>
int	main(void)
{
	//printf("%d\n", ft_atoi("  	-123456"));
	printf("%d", atoi("  	 --12345aaa6"));
	return (0);
}*/
