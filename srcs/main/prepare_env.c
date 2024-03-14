/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:06:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/14 17:47:15 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	adjust_shlevel(char **env, t_data *node)
{
	int				i;
	long long int	shlvl;
	char			*line;
	char			*var_value;

	i = -1;
	shlvl = 0;
	while (env[++i])
	{
		if (ft_strstr(env[i], "SHLVL="))
		{
			var_value = ft_getenv("SHLVL", node);
			shlvl = ft_atoll(var_value) + 1;
			var_value = ft_itoa(shlvl);
			if (!var_value)
				env_quit(env, node);
			line = ft_strjoin("SHLVL=", var_value, 0);
			free(var_value);
			if (!line)
				env_quit(env, node);
			if (handle_var_exist_in_envp(node, line) == 1)
				env_quit(env, node);
			free(line);
		}
	}
}

char	**prepare_basic_envs(t_data *node)
{
	char	**result;
	char	*home;

	result = ft_calloc(sizeof(char *), 5);
	if (!result)
		env_quit(NULL, node);
	home = ft_strdup(getcwd(NULL, 0));
	if (!home)
		env_quit(result, node);
	result[0] = ft_strjoin("HOME=", home, 0);
	free(home);
	if (!result[0])
		env_quit(result, node);
	result[1] = ft_strdup("SHLVL=\"1\"");
	if (!result[1])
		env_quit(result, node);
	result[2] = ft_strdup("PATH=\"/usr/bin:\"");
	if (!result[2])
		env_quit(result, node);
	result[3] = ft_strdup("_=/usr/bin/env");
	if (!result[3])
		env_quit(result, node);
	result[4] = NULL;
	return (result);
}

void	add_missing_envs(t_data *node)
{
	char *pwd;
	char *exp;

	if (!getenv("PATH"))
		handle_export(node, "PATH=\"/usr/bin:\"");
	if (!getenv("SHLVL"))
		handle_export(node, "SHLVL=\"1\"");
	if (!getenv("_"))
		handle_export(node, "_=\"/usr/bin/env\"");
	if (!getenv("PWD"))
	{
		pwd = get_current_directory();
		exp = ft_strjoin("PWD=", pwd, 0);
		if (!exp)
		{
			ft_free_array(node->envp);
			free(node->oldpwd);
			free(node);
			handle_error("env preparation failed", -1);
		}
		handle_export(node, exp);
		free(exp);
	}
}

char	**dup_envp(char **envp, t_data *node)
{
	int		counter;
	char	**result;
	int		counter2;

	(void)node;
	counter = 0;
	while (envp[counter])
		counter++;
	if (!counter)
		return (prepare_basic_envs(node));
	result = malloc(sizeof(char *) * (counter + 1));
	if (!result)
		return (NULL);
	counter2 = 0;
	while (counter2 <= counter)
		result[counter2++] = NULL;
	counter2 = 0;
	while (counter2 < counter)
	{
		result[counter2] = ft_strdup(envp[counter2]);
		if (!result[counter2])
			return (NULL);
		counter2++;
	}
	return (result);
}
