/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:06:20 by msumon            #+#    #+#             */
/*   Updated: 2024/03/14 16:46:23 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(char *str)
{
	int		i;
	char	*output;

	i = 0;
	output = malloc(sizeof(char) * (ft_strlen_till_char(str, ' ') + 1));
	if (!output)
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\n'
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '-' && str[i] != '.')
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*handle_dollar_question(char *result, t_data *node, int *i)
{
	char	*var_value;

	var_value = ft_lastval_str(node);
	result = ft_strjoin(result, var_value, 1);
	if (!result)
		ft_exit(node, -1, "malloc failed at handle envp");
	free(var_value);
	(*i)++;
	return (result);
}

char	*handle_env_values(char *str, char *result, t_data *node, int *i)
{
	char	*var_name;
	char	*tmp;

	if ((str[(*i) + 1] >= 'A' && str[(*i) + 1] <= 'Z') || (str[(*i) + 1] >= 'a'
			&& str[(*i) + 1] <= 'z'))
	{
		var_name = extract_var_name(str + (*i) + 1);
		if (!var_name)
			ft_exit(node, -1, "malloc failed at handle envp");
		tmp = get_env_value(var_name, node);
		result = ft_strjoin(result, tmp, 1);
		if (!result)
		{
			free(var_name);
			ft_exit(node, -1, "malloc failed at handle envp");
		}
		(*i) += ft_strlen(var_name);
		free(var_name);
	}
	else
		char_append(&result, str[(*i)]);
	return (result);
}

char	*handle_envp(char *str, t_data *node)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		ft_exit(node, -1, "malloc in handle_envp failed");
	result[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				result = handle_dollar_question(result, node, &i);
			else
				result = handle_env_values(str, result, node, &i);
		}
		else
			char_append(&result, str[i]);
		i++;
	}
	return (result);
}
