/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:37:29 by msumon            #+#    #+#             */
/*   Updated: 2024/03/10 14:52:31 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(char *error, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit (status);
}

void	nocomm_error(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	directory_error(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void    parse_error(t_data *node, int flag, char *msg, int value)
{
    if (flag)
    {
        free_tokens(node->tokens, node->processes);
    }
    if (node->std_in != -1)
        close(node->std_in);
    if (node->std_out != -1)
        close(node->std_out);
    ft_free_array(node->envp);
    free(node->input_line);
    free(node);
    handle_error(msg, value);
}
