/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:41:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/08 13:53:19 by mhuszar          ###   ########.fr       */
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
    close(node->std_in);
    close(node->std_out);
}

void    ft_exit(t_data *node, t_token *head, char *line)
{
    free_tokens(&head);
    free_node(node);
    free(line);
    exit(0);
}
