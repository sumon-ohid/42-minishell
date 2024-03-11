/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:24 by msumon            #+#    #+#             */
/*   Updated: 2024/03/11 21:54:37 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes_env(char c, int *in_quotes, char *quote_char)
{
	if (*in_quotes && *quote_char == c)
	{
		*in_quotes = 0;
	}
	else if (!*in_quotes)
	{
		*in_quotes = 1;
		*quote_char = c;
	}
}

void	print_env_var(char *env_var)
{
	int		j;
	int		in_quotes;
	char	quote_char;

	j = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (env_var[j])
	{
		if ((env_var[j] == '\'' || env_var[j] == '\"') && (j == 0 || env_var[j
					- 1] != '\\'))
		{
			handle_quotes_env(env_var[j], &in_quotes, &quote_char);
			j++;
			continue ;
		}
		if (in_quotes && env_var[j] == ' ')
		{
			j++;
			continue ;
		}
		ft_putchar(env_var[j]);
		j++;
	}
	ft_putchar('\n');
}

char	**ft_env(t_data *node)
{
	int		i;
	char	**envp;

	i = 0;
	envp = node->envp;
	while (envp[i])
	{
		print_env_var(envp[i]);
		i++;
	}
	return (envp);
}
