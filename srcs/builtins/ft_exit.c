/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:41:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/12 22:35:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	digit_checker(char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	if (str[counter] == '+' || str[counter] == '-')
		counter++;
	if (!str[counter])
		return (0);
	while (str[counter] >= '0' && str[counter] <= '9')
		counter++;
	if (!str[counter] && check_atoll(str))
		return (1);
	else
		return (0);
}

int	exit_too_many_args(t_data *node)
{
	node->last_return = -1;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (-1);
}

int	exit_with_args(t_data *node, int exit_val, t_token *head, int val)
{
	int		counter;

	counter = 0;
	while (head)
	{
		if (head->type == FLAG)
		{
			if (!digit_checker(head->str) && counter == 0)
			{
				printf("exit\n");
				ft_printerr("minishell: exit: %s: numeric %s\n",
					head->str, "argument required");
				ft_exit(node, 2, NULL);
			}
			val = ft_atoll(head->str);
			counter++;
		}
		head = head->next;
	}
	if (counter > 1)
		return (exit_too_many_args(node));
	else if (counter == 0)
		ft_exit(node, exit_val, NULL);
	return (ft_exit(node, (unsigned char)val, NULL), 0);
}

void	ft_early_exit(t_data *node, int exit_val, char *msg)
{
	free(node->input_line);
	ft_free_array(node->envp);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node);
	if (msg)
		handle_error(msg, exit_val);
	else
		exit(exit_val);
}

void	ft_exit(t_data *node, int exit_val, char *msg)
{
	free_node(node);
	if (msg)
		handle_error(msg, exit_val);
	else
		exit(exit_val);
}
