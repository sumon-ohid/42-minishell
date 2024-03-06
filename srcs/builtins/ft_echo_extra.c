/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:32:22 by msumon            #+#    #+#             */
/*   Updated: 2024/03/06 16:15:14 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// I think this function is not used anywhere in the project
void	handle_quotes(char *arg, int *i, int len)
{
	char	*new_arg;

	if ((arg[0] == '\'' && arg[len - 1] == '\'') || (arg[0] == '\"' && arg[len
				- 1] == '\"'))
	{
		new_arg = ft_substr(arg, 1, len - 2);
		ft_putstr(new_arg);
		*i = len;
	}
	else if ((arg[0] == '\'' && arg[len - 1] != '\'') || (arg[0] == '\"'
			&& arg[len - 1] != '\"'))
		return ;
	else if ((arg[0] != '\'' && arg[len - 1] == '\'') || (arg[0] != '\"'
			&& arg[len - 1] == '\"'))
		return ;
}

void	print_argument(char *arg, t_data *node)
{
	int	i;

	i = 0;
	(void)node;
	if (ft_strcmp(arg, "\"\'\"") == 0)
	{
		ft_putstr("\'");
		return ;
	}
	if (ft_strcmp(arg, "\'\"\'") == 0)
	{
		ft_putstr("\"");
		return ;
	}
	while (arg[i])
	{
		if (arg[i] == '~')
			ft_putstr(getenv("HOME"));
		else
			ft_putchar(arg[i]);
		i++;
	}
	return ;
}

char	*copy_after_char(char *str, char c)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	if (ft_strchr(str, c) == 0)
		return (ft_strdup(""));
	while (str[i] != c)
		i++;
	i++;
	output = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	if (!output)
		return (NULL);
	while (str[i])
	{
		output[j] = str[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}
