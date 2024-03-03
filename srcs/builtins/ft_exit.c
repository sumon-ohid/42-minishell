/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:41:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/03 22:58:47 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
typedef struct s_data
{
	char			*line_for_export;
	int				**fd;
	int				*pid;
	char				**envp; //no free
	char				*oldpwd; //no free EXCEPT IF WE EVER USE CD
						- should change this in CD
	char				*pwd; //no free EXCEPT IF WE EVER USE CD
						- should change this in CD
	char				*home; //no_free
	char			*line_temp;
	struct s_data	*next;
}						t_data;*/

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

void	ft_free_fds(t_data *node)
{
	int	i;
	int	**arr;

	i = 0;
	close_all(&node->fd, node->processes - 1);
	arr = node->fd;
	if (!arr)
		return ;
	while (i < node->processes - 1)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return ;
}

void	free_vars(t_vars *local_vars)
{
	t_vars	*cur;
	t_vars	*prev;

	cur = local_vars;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->str);
		free(prev->first_half);
		free(prev->second_half);
		free(prev);
	}
}

void	free_node(t_data *node)
{
	free_tokens(node->tokens, node->processes);
	free_vars(node->local_vars);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node->input_line);
	if (node->status)
		free(node->status);
	node->status = NULL;
	if (node->pid)
		free(node->pid);
	node->pid = NULL;
	ft_free_array(node->arr);
	ft_free_array(node->envp);
	free(node);
}

int	digit_checker(char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	if (str[counter] == '+' || str[counter] == '-')
		counter++;
	while (str[counter] >= '0' && str[counter] <= '9')
		counter++;
	if (!str[counter] && counter < 20)
		return (1);
	else
		return (0);
}

int	exit_with_args(t_data *node, int exit_val, t_token *head)
{
	t_token *proxy;
	int		counter;
	int		val;
	
	proxy = head;
	counter = 0;
	while (proxy)
	{
		if (proxy->type == FLAG)
		{
			if (!digit_checker(proxy->str))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", proxy->str);
				ft_exit(node, 2, NULL);
			}
			val = ft_atoi(proxy->str);
			counter++;
		}
		proxy = proxy->next;
	}
	if (counter > 1)
		return (printf("exit\nminishell: exit: too many arguments\n"));
	else if (counter == 0)
		ft_exit(node, exit_val, NULL);
	return (ft_exit(node, (unsigned char)val, NULL), 0);
}

void	ft_early_exit(t_data *node, int exit_val, char *msg)
{
	free(node->input_line);
	ft_free_array(node->envp);
	ft_free_array(node->arr);
	free_vars(node->local_vars);
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
