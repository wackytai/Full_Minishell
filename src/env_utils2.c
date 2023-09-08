/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:29:15 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/08 10:40:15 by tlemos-m         ###   ########.fr       */
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
	if (var[i] != '=')
		temp[1] = 0;
	else if (var[i] == '=' && !var[i + 1])
		temp[1] = ft_strdup("");
	else
		temp[1] = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	return (temp);
}

t_tokens	*get_env_node(t_tokens *env, char *str)
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

	temp = get_env_node(data->env, "PWD");
	s1 = 0;
	if (!ft_strcmp(str, temp->content))
		return ;
	s1 = getcwd(s1, 0);
	temp = get_env_node(data->env, "OLDPWD");
	free(temp->content);
	temp->content = ft_strdup(get_env_node(data->env, "PWD")->content);
	temp = get_env_node(data->env, "PWD");
	free(temp->content);
	temp->content = s1;
	return ;
}

void	reset_rank(t_tokens **lst)
{
	t_tokens	*head;

	head = *lst;
	while (*lst)
	{
		(*lst)->rank = 0;
		*lst = (*lst)->next;
	}
	*lst = head;
}

int	remove_env_node(t_tokens **env, char *name)
{
	t_tokens	*temp;
	t_tokens	*new_temp;
	t_tokens	*prev_node;

	temp = get_env_node(*env, name);
	if (!temp)
		return (set_exit_code(0, true));
	new_temp = temp->next;
	prev_node = temp->prev;
	if (prev_node)
		prev_node->next = new_temp;
	else
		*env = new_temp;
	if (new_temp)
		new_temp->prev = prev_node;
	if (temp->content)
		free(temp->content);
	free(temp->var);
	free(temp);
	get_rank(env);
	return (set_exit_code(0, true));
}
