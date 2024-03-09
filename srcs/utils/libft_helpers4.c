/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:48:37 by msumon            #+#    #+#             */
/*   Updated: 2024/03/09 17:50:09 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strjoin_node(char *s1, char *s2, int save_flag, t_data *node)
{
	int		ctr1;
	int		ctr2;
	char	*new_str;

	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		ft_exit(node, -1, "malloc failed at strjoin");
	ctr1 = 0;
	ctr2 = 0;
	while (s1[ctr1])
	{
		new_str[ctr1] = s1[ctr1];
		ctr1++;
	}
	while (s2[ctr2])
		new_str[ctr1++] = s2[ctr2++];
	new_str[ctr1] = '\0';
	if (save_flag)
		free(s1);
	return (new_str);
}
void	ft_lstadd_back(t_element **lst, t_element *nw)
{
	t_element *proxy;
	
	if (!new || !lst)
		return ;
	proxy = *lst;
	if (!proxy)
		*lst = nw;
	else
	{
		while (proxy->next)
			proxy = proxy->next;
		proxy->next = nw;
	}
}

