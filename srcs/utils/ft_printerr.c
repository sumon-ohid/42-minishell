/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:58:51 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/12 13:42:02 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_s(char *str)
{
	int	counter;

	counter = 0;
	if (str == NULL)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (str[counter])
	{
		write(2, &str[counter], 1);
		counter++;
	}
	return (counter);
}

int	print_c(char c)
{
	write(2, &c, 1);
	return (1);
}

int	printf_sub(va_list arg_list, const char typ)
{
	int	len;

	len = 0;
	if (typ == 'c')
		len = print_c(va_arg(arg_list, int));
	else if (typ == 's')
		len = print_s(va_arg(arg_list, char *));
	else if (typ == '%')
		len = print_c('%');
	return (len);
}

int	flags_check(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i')
		return (1);
	else if (c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	else
		return (0);
}

int	ft_printerr(const char *tipus, ...)
{
	int		counter;
	int		len;
	va_list	arg_list;

	va_start(arg_list, tipus);
	counter = 0;
	len = 0;
	while (tipus[counter])
	{
		if (tipus[counter] == '%')
		{
			counter++;
			if (!flags_check(tipus[counter]))
				return (-1);
			else
				len = len + printf_sub(arg_list, tipus[counter]);
		}
		else
			len = len + print_c(tipus[counter]);
		counter++;
	}
	va_end(arg_list);
	return (len);
}

