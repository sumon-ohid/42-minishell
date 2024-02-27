/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:57 by msumon            #+#    #+#             */
/*   Updated: 2024/02/27 10:04:15 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cleanup(t_data *node, t_token **tokens, char *line, char **arr)
{
	free_tokens(tokens, node->processes);
	free(line);
	free_arr(arr);
}
