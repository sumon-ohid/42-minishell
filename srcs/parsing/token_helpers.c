/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:28:51 by msumon            #+#    #+#             */
/*   Updated: 2024/02/29 14:13:43 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_until_char(char *str, char c)
{
	int		i;
	char	*output;

	i = 0;
	if (ft_strchr(str, c) == 0)
		return (ft_strdup(str));
	while (str[i] && str[i] != c)
		i++;
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		handle_error("malloc in copy_until_char failed", 1);
	i = 0;
	while (str[i] && str[i] != c)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	ft_strlen_till_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	char_append(char **str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!new_str)
		handle_error("malloc in char_append failed", 1);
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
}
