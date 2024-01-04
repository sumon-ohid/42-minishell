/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/03 20:17:54 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node(t_history **history, char *str)
{
	t_history *entry;
	t_history *proxy;

	entry = malloc(sizeof(t_history));
	entry->string = ft_strdup(str);
	entry->next = NULL;
	if (!*history)
		*history = entry;
	else
	{
		proxy = *history;
		while (proxy->next)
			proxy = proxy->next;
		proxy->next = entry;
	}
}
/*
int main(void)
{
	using_history();
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			break ;
		else if (*input)
			add_history(input);
		free(input);
	}
	clear_history();
	write(1, "exiting minishell\n", 17);
	return (0);
}*/

int main(void)
{
	char		*input;
	t_history	*history;
	
	history = NULL;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			break ;
		else if (*input)
			append_node(&history, input);
		free(input);
	}
	//clear_history(); TODO: freeing function
	write(1, "exiting minishell\n", 17);
	return (0);
}
