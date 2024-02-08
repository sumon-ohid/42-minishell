/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:41:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/08 18:48:01 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
typedef struct s_data
{
	char				*line_for_export;
	int					**fd;
	int					*pid;
	char				**envp; //no free
	char				*oldpwd; //no free EXCEPT IF WE EVER USE CD - should change this in CD
	char				*pwd; //no free EXCEPT IF WE EVER USE CD - should change this in CD
	char				*home; //no_free
	char				*line_temp;
	struct s_data		*next;
}						t_data;*/

void free_node(t_data *node)
{
    free_tokens(node->tokens, node->processes);
	close(node->std_in);
    close(node->std_out);
	free(node->input_line);
	ft_free_array(node->arr);
	free(node);
}

void    ft_exit(t_data *node, int exit_val)
{
	free_node(node);
    exit(exit_val);
}
