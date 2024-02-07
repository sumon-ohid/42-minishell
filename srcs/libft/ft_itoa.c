/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:16:13 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/07 13:36:38 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	digit_counter(long int y)
{
	int	counter;

	counter = 1;
	while (y > 9)
	{
		y = y / 10;
		counter++;
	}
	return (counter);
}

static int	turning(char *result, int counter, int digits, long int n)
{
	while (counter < digits)
	{
		result[counter] = '0' + (n % 10);
		n = n / 10;
		counter++;
	}
	return (counter);
}

static void	rev_str_tab(char *tab, int size, int negative)
{
	int	counter;
	int	storage1;
	int	storage2;
	int	positive;
	int	p_size;

	counter = 0;
	positive = 0;
	p_size = size;
	if (!negative)
		positive = 1;
	if ((size % 2 == 1) && negative)
		p_size++;
	while (counter < (p_size / 2))
	{
		storage1 = tab[counter];
		storage2 = tab[size - counter - positive];
		tab[counter] = storage2;
		tab[size - counter - positive] = storage1;
		counter++;
	}
}

char	*ft_itoa(int n)
{
	char		*result;
	int			counter;
	int			negative;
	int			digits;
	long int	proxy;

	counter = 0;
	negative = 0;
	proxy = (long int )n;
	if (n < 0)
	{
		negative = 1;
		proxy = proxy * -1;
	}
	digits = digit_counter(proxy);
	result = (char *)malloc((digits + 1 + negative) * 1);
	if (!result)
		return (0);
	counter = turning(result, counter, digits, proxy);
	if (negative)
		result[counter++] = '-';
	result[counter] = '\0';
	rev_str_tab(result, digits, negative);
	return (result);
}
/*
int	main(void)
{
	printf("%d\n", digit_counter(2147483648));
	printf("%s", ft_itoa(-2123456));
	return (0);
}*/
