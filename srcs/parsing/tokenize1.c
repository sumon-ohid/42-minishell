/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by msumon            #+#    #+#             */
/*   Updated: 2024/02/10 12:54:33 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

/*if (ft_strstr(str, "\""))
 DO SOMETHING HERE!*/

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

char	*copy_until_char(char *str, char c)
{
	int		i;
	char	*output;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		handle_error("malloc in copy_until_char failed", 1);
	i = 0;
	while (str[i] && str[i] != c)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	ft_strlen_till_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void char_append(char **str, char c)
{
	char *new_str;
	int i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!new_str)
		handle_error("malloc in char_append failed", 1);
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
}

char *extract_var_name(char *str, t_data *node)
{
	int i;
	char *output;

	i = 0;
	output = malloc(sizeof(char) * (ft_strlen_till_char(str, ' ') + 1));
	if (!output)
		ft_exit(node, 1, "malloc in extract_var_name failed");
	while (str[i] && str[i] != ' ')
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*handle_envp(char *str, t_data *node)
{
    char *result;
    char *var_name;
    char *var_value;
    int i;

    i = 0;
    result = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!result)
        ft_exit(node, 1, "malloc in handle_envp failed");
    result[0] = '\0';
	if (ft_strcmp(str, "$?") == 0) //they could be part of a bigger string, should be considered, maybe this should be moved to get_env_value
         return (ft_lastval_str(node));
    if (ft_strcmp(str, "$") == 0)
         return (ft_strdup("$"));
    while (str[i])
    {
        if (str[i] != '$')
        {
            char_append(&result, str[i]);
        }
        else
        {
            var_name = extract_var_name(str + i + 1, node);
            var_value = get_env_value(var_name, node);
            result = ft_strjoin(result, var_value, 1);
            i += ft_strlen(var_name);
			free(var_name);
        }
        i++;
    }
	return (result);
}


// char	*handle_envp(char *str, t_data *node)
// {
//     char **split_str;
//     char *result;
// 	char *tmp;
// 	char *new_result;
//     int i;

//     i = 0;
//     result = malloc(sizeof(char) * (ft_strlen(str) + 1));
//     if (!result)
//         handle_error("malloc in handle_envp failed", 1);
//     result[0] = '\0';
//     split_str = ft_split(str, ' ', 0, 0);
//     if (!split_str)
//         handle_error("malloc in handle_envp failed", 1);
//     if (ft_strcmp(str, "$?") == 0) //they could be part of a bigger string, should be considered, maybe this should be moved to get_env_value
//         return (ft_lastval_str(node));
//     if (ft_strcmp(str, "$") == 0)
//         return (ft_strdup("$"));
//     while (split_str[i])
//     {
//         if (ft_strstr(split_str[i], "$"))
//         {
// 			tmp = copy_until_char(split_str[i], '$');
// 			if (tmp) //this part leads to leaks cause of overwriting, check save flags you pass
// 			{
// 				new_result = ft_strjoin(result, tmp, 0);
//             	result = new_result;
// 				new_result = ft_strjoin(result, get_env_value(copy_after_char(split_str[i], '$'), node), 1);
//             	result = new_result;
// 			}
// 			else
// 			{
// 				new_result = ft_strjoin(result, get_env_value(split_str[i], node), 1);
//             	result = new_result;
// 			}
//         }
//         else
//         {
//             new_result = ft_strjoin(result, split_str[i], 1);
//             result = new_result;
//         }
//         i++;
// 		new_result = ft_strjoin(result, " ", 1);
// 		result = new_result;
//     }
//     ft_free_array(split_str);
//     return (result);
// }

int	check_builtins(char *word)
{
	if (!word)
		return (-1);
	else if (ft_strcmp(word, "cd") == 0)
		return (0);
	else if (ft_strcmp(word, "echo") == 0)
		return (0);
	else if (ft_strcmp(word, "env") == 0)
		return (0);
	else if (ft_strcmp(word, "clear") == 0)
		return (0);
	else if (ft_strcmp(word, "pwd") == 0)
		return (0);
	else if (ft_strcmp(word, "exit") == 0)
		return (0);
	else if (ft_strcmp(word, "export") == 0)
		return (0);
	else if (ft_strcmp(word, "unset") == 0)
		return (0);
	else
		return (-1);
}

int	check_assign(char *word)
{
	int	counter;

	counter = 0;
	if (!word)
		return (0);
	while (word[counter])
	{
		if (word[counter] == '=')
			return (1);
		counter++;
	}
	return (0);
}

int	check_prevs(char *word, int prev_type)
{
	if (!word)
		return (0);
	else if (check_assign(word))
		return (SET);
	else if (prev_type == HEREDOC)
		return (DELIM);
	else if (prev_type == REDIR_OUT)
		return (OUTFILE);
	else if (prev_type == REDIR_OUT_APPEND)
		return (OUTFILE_APPEND);
	else if (prev_type == REDIR_IN)
		return (INFILE);
	else if (prev_type == BUILTIN || prev_type == COMMAND || prev_type == FLAG)
		return (FLAG);
	else
		return (COMMAND);
}
