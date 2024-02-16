/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:32:22 by msumon            #+#    #+#             */
/*   Updated: 2024/02/16 09:00:37 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_dollar(char *arg, int *i, t_data *node)
{
	if (arg[*i + 1] == '?')
		ft_putnbr(0);
	else if (arg[*i + 1] == '$')
		ft_putnbr(getpid());
	else if (arg[*i + 1] == '0')
		ft_putstr("minishell");
	else
	{
		ft_putstr(get_env_value(arg + 1, node));
		return ;
	}
	(*i)++;
}

void	handle_quotes(char *arg, int *i, int len)
{
	char	*new_arg;

	if ((arg[0] == '\'' && arg[len - 1] == '\'')
		|| (arg[0] == '\"' && arg[len - 1] == '\"'))
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
	if (arg[0] == '\'' && arg[1] == '\0')
		return ;
	else if (arg[0] == '\"' && arg[1] == '\0')
		return ;
	while (arg[i])
	{
		if (arg[i] == '~')
			ft_putstr(getenv("HOME"));
		else if (arg[i] == '*')
			show_dir();
		ft_putchar(arg[i]);
		i++;
	}
	return ;
}
