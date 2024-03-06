/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:27:58 by msumon            #+#    #+#             */
/*   Updated: 2024/03/06 16:35:49 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_helper_pipes(char *s, char c, size_t *i, char *output)
{
	char	quote;
	int		flag;
	int		k;

	quote = 0;
	flag = 0;
	k = 0;
	while (s[*i] && (s[*i] != c || quote))
	{
		if (!flag && (s[*i] == '\'' || s[*i] == '\"'))
		{
			quote = s[*i];
			flag = 1;
		}
		else if (flag && (s[*i] == quote))
		{
			flag = 0;
			quote = 0;
		}
		output[k++] = s[(*i)++];
	}
	output[k] = '\0';
}
