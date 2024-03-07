/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mole_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:05:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/07 13:27:08 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parse_error(t_data *node)
{
    ft_free_array(node->envp);
    free(node->tokens);
    free(node->input_line);
    handle_error("mole parser failed", -1);
}

char	*ft_substr_clean(char const *s, unsigned int start, size_t len, t_data *node)
{
	unsigned int	counter;
	char			*sub_str;

	counter = start;
	if (start >= ((unsigned int)ft_strlen(s)))
		return (NULL);
	while (s[counter])
		counter++;
	if ((counter - start) < len)
		sub_str = (char *)malloc(sizeof(char) * ((counter - start) + 1));
	else
		sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		parse_error(node);
	counter = 0;
	while (len && s[start])
	{
		sub_str[counter++] = s[start++];
		len--;
	}
	sub_str[counter] = '\0';
	return (sub_str);
}

bool    is_delim(char c, char quote)
{
    if (c == ' ' && !quote)
        return (true);
    else if (c == '\t' && !quote)
        return (true);
    else if (c == '\n' && !quote)
        return (true);
    else if (c == '\0')
        return (true);
    else if (c == '|' && !quote)
        return (true);
    else if (c == '<' && !quote)
        return (true);
    else if (c == '>' && !quote)
        return (true);
    else if (c == '\"' && quote == '\"')
        return (true);
    else if (c == '\'' && quote == '\'')
        return (true);
    else
        return (false);
}
