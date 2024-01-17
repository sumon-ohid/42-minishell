/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by sumon             #+#    #+#             */
/*   Updated: 2024/01/17 09:58:32 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_envp(char *str)
{
	char	*output;

	output = getenv(str + 1);
	if (!output)
		output = ft_strdup("\n");
	free(str);
	return (output);
}
