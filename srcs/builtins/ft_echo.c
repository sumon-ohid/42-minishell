/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 13:35:57 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_after_char(char *str, char c)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	while (str[i] != c)
		i++;
	i++;
	output = malloc(sizeof(char) * ft_strlen(str + i));
	while (str[i])
	{
		output[j] = str[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}

char	*get_env_value(char *arg, t_data *node)
{
	char	*env_value;
	int		i;

	i = 0;
	while (node->envp[i])
	{
		if (ft_strstr(node->envp[i], arg) != 0)
		{
			env_value = copy_after_char(node->envp[i], '=');
			return (env_value);
		}
		i++;
	}
	return ("");
}

void	show_dir(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			ft_putstr(dir->d_name);
			ft_putchar(' ');
		}
	}
	closedir(d);
}

void	handle_dollar(char *arg, int *i, t_data *node)
{
    if (arg[*i + 1] == '?')
        ft_putnbr(0);
    else if (arg[*i + 1] == '$')
        ft_putnbr(getpid());
    else if (arg[*i + 1] == '0')
        ft_putstr("minishell");
    else
    {
        ft_putstr(get_env_value(arg + 1, node));
        return ;
    }
    (*i)++;
}

void	handle_quotes(char *arg, int *i, int len)
{
    char *new_arg;

    if ((arg[0] == '\'' && arg[len - 1] == '\'') || (arg[0] == '\"' && arg[len - 1] == '\"'))
    {
        new_arg = ft_substr(arg, 1, len - 2);
        ft_putstr(new_arg);
        free(new_arg);
        *i = len;
    }
    else if ((arg[0] == '\'' && arg[len - 1] != '\'') || (arg[0] == '\"' && arg[len - 1] != '\"'))
        return ;
    else if ((arg[0] != '\'' && arg[len - 1] == '\'') || (arg[0] != '\"' && arg[len - 1] == '\"'))
        return ;
}

void	print_argument(char *arg, t_data *node)
{
    int		i;
    int		len;

    i = 0;
    len = ft_strlen(arg);
    if (arg[0] == '\'' && arg[1] == '\0')
        return ;
    else if (arg[0] == '\"' && arg[1] == '\0')
        return ;
    while (arg[i])
    {
        if (arg[i] == '$' && arg[i + 1])
            handle_dollar(arg, &i, node);
        else if (arg[i] == '~')
            ft_putstr(getenv("HOME"));
        else if (arg[i] == '*')
            show_dir();
        else
            handle_quotes(arg, &i, len);
        ft_putchar(arg[i]);
        i++;
    }
    return ;
}

// void	print_argument(char *arg, t_data *node)
// {
// 	int		i;
// 	int		len;
// 	char	*new_arg;

// 	i = 0;
// 	len = ft_strlen(arg);
// 	if (arg[0] == '\'' && arg[1] == '\0')
// 		return ;
// 	else if (arg[0] == '\"' && arg[1] == '\0')
// 		return ;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '$' && arg[i + 1])
// 		{
// 			if (arg[i + 1] == '?')
// 				ft_putnbr(0);
// 			else if (arg[i + 1] == '$')
// 				ft_putnbr(getpid());
// 			else if (arg[i + 1] == '0')
// 				ft_putstr("minishell");
// 			else
// 			{
// 				ft_putstr(get_env_value(arg + 1, node));
// 				return ;
// 			}
// 			i++;
// 		}
// 		else if (arg[i] == '~')
// 			ft_putstr(getenv("HOME"));
// 		else if (arg[i] == '*')
// 			show_dir();
// 		else if ((arg[0] == '\'' && arg[len - 1] == '\'') || (arg[0] == '\"'
// 				&& arg[len - 1] == '\"'))
// 		{
// 			new_arg = ft_substr(arg, 1, len - 2);
// 			ft_putstr(new_arg);
// 			free(new_arg);
// 			i = len;
// 		}
// 		else if ((arg[0] == '\'' && arg[len - 1] != '\'') || (arg[0] == '\"'
// 				&& arg[len - 1] != '\"'))
// 			return ;
// 		else if ((arg[0] != '\'' && arg[len - 1] == '\'') || (arg[0] != '\"'
// 				&& arg[len - 1] == '\"'))
// 			return ;
// 		else
// 			ft_putchar(arg[i]);
// 		i++;
// 	}
// 	return ;
// }

void	ft_echo(char *line, t_data *node, t_token *head)
{
	int fl;
	int newline;

	newline = 1;
	fl = 0;
	(void)line;
	if (head->next && ft_strcmp(head->next->str, "-n") == 0)
	{
		newline = 0;
		head = head->next->next;
	}
	while (head)
	{
		if (head->type == FLAG)
		{
			if (fl)
				ft_putchar(' ');
			if (ft_strcmp(head->str, "$?") == 0) //TODO: handle other cases with it embedded in string etc.
				ft_lastvalue(node);
			else
				print_argument(head->str, node);
			fl = 1;
		}
		head = head->next;
	}
	if (newline)
		ft_putchar('\n');
}

// echo "$HOME" need to fix.
//  echo asas =sas this does not behave like bash