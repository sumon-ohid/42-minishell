/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 17:06:47 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	flag_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	remove_quote_if_inside_no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1] == '\'' || str[i + 1] == '\"')
				ft_strcpy(str + i, str + i + 2);
			else
				i++;
		}
		else
			i++;
	}
}

void	process_flags(t_token **head, int *newline)
{
	if ((*head)->next && flag_check((*head)->next->str))
	{
		*newline = 0;
		while ((*head)->next)
		{
			if (!flag_check((*head)->next->str))
				break ;
			*head = (*head)->next;
		}
	}
	*head = (*head)->next;
}

void	process_arguments(t_token *head, t_data *node, int *fl)
{
	while (head)
	{
		if (head->type == FLAG)
		{
			if (*fl)
				ft_putchar(' ');
			print_argument(head->str, node);
			*fl = 1;
		}
		head = head->next;
	}
}

void	ft_echo(char *line, t_data *node, t_token *head)
{
	int	fl;
	int	newline;

	newline = 1;
	fl = 0;
	(void)line;
	process_flags(&head, &newline);
	process_arguments(head, node, &fl);
	if (newline)
		ft_putchar('\n');
}
