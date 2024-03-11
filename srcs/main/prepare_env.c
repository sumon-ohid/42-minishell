/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:06:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/10 18:44:37 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void    adjust_shlevel(char **env, t_data *node)
{
    //we will write this tomorrow
}*/

void    env_quit(char **result, t_data *node)
{
    if (result)
        ft_free_array(result);
    free(node);
    handle_error("env preparation failed", -1);
}

char    **prepare_basic_envs(t_data *node)
{
    char **result;
    char *home;

    result = ft_calloc(sizeof(char *), 4); //maybe this is not enough for setting to null
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
    if (!result[0])
        env_quit(result, node);
    result[2] = ft_strdup("PATH=\"/usr/bin\"");
    if (!result[0])
        env_quit(result, node);
    result[3] = NULL;
    return (result);
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
	/*if (!counter)
		return (prepare_basic_envs(node));*/
	result = malloc(sizeof(char *) * counter);
	if (!result)
		return (NULL);
	counter2 = 0;
	while (counter2 < counter)
		result[counter2++] = NULL;
	counter2 = 0;
	while (counter2 < counter - 1)
	{
		result[counter2] = ft_strdup(envp[counter2]);
		if (!result[counter2])
			return (NULL);
		counter2++;
	}
	//adjust_shlevel(result, node);
	return (result);
}
