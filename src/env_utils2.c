/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:29:15 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/05 14:09:53 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env_var(char *var)
{
	char	**temp;
	int		i;

	i = -1;
	temp = (char **)malloc(sizeof(char *) * 3);
	temp[2] = 0;
	while (var[++i] && var[i] != '=')
		continue ;
	temp[0] = ft_substr(var, 0, i);
	temp[1] = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	return (temp);
}

t_tokens	*env_var(t_tokens *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->var, str))
			return (env);
		env = env->next;
	}
	return (0);
}

void	update_dirs(t_data *data, char *str)
{
	t_tokens	*temp;
	char		*s1;

	temp = env_var(data->env, "PWD");
	s1 = 0;
	if (!ft_strcmp(str, temp->content))
		return ;
	s1 = getcwd(s1, 0);
	temp = env_var(data->env, "OLDPWD");
	free(temp->content);
	temp->content = ft_strdup(env_var(data->env, "PWD")->content);
	printf("OLDPWD: %s\n", temp->content);
	temp = env_var(data->env, "PWD");
	free(temp->content);
	temp->content = s1;
	printf("PWD: %s\n", temp->content);
	return ;
}
