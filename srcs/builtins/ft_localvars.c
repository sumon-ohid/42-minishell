/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_localvars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:17:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/16 08:14:23 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_vars  *create_vars_node(char *str, t_data *node)
{
    int     counter;
    t_vars  *new;

    counter = 0;
    new = malloc(sizeof(t_vars));
    if (!new)
        ft_exit(node, 127, "malloc error in create_vars");
    while (str[counter] && str[counter] != '=')
        counter++;
    new->first_half = ft_substr(str, 0, counter);
    new->second_half = ft_substr(str, counter + 1, ft_strlen(str) - counter);
    new->str = ft_strdup(str);
    if (!new->str || !new->first_half || !new->second_half)
        ft_exit(node, 127, "malloc error in create_vars");
    new->next = NULL;
    new->deprecated = 0;
    //printf("we created some strings: %s, %s and %s\n", new->str, new->first_half, new->second_half);
    return (new);
}

void    refresh_values(t_vars **vars)
{
    t_vars  *proxy;
    t_vars  *checker;

    proxy = *vars;
    checker = proxy->next;
    while (proxy && checker)
    {
        while (checker)
        {
            if (ft_strcmp(proxy->first_half, checker->first_half) == 0)
            {
                proxy->deprecated = 1;
                //printf("%s is now deprecated\n", proxy->str);
            }
            checker = checker->next;
        }
        proxy = proxy->next;
        checker = proxy->next;
    }
}


void    store_in_list(char *str, t_data *node)
{
    t_vars  *proxy;

    proxy = node->local_vars;
    if (!proxy)
        node->local_vars = create_vars_node(str, node);
    else
    {
        while (proxy->next)
            proxy = proxy->next;
        proxy->next = create_vars_node(str, node);
        refresh_values(&node->local_vars);
    }
}

void    ft_localvars(t_token **tokens, t_data *node, int processes)
{
    t_token	*proxy;
	int		counter;

	counter = 0;
	while (counter < processes)
	{
		proxy = tokens[counter];
		if (!proxy)
			return ;
		while (proxy)
		{
			if (ft_strstr(proxy->str, "=") && proxy->quote == NO_QUOTE)
                store_in_list(proxy->str, node);
            proxy = proxy->next;
		}
		counter++;
	}
}
