/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:49:43 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/11 09:10:40 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This functions adds environment variables to a linked list */
void	get_env(char **envp, t_data *data)
{
	int		i;
	char	**temp;

	i = -1;
	data->env = 0;
	data->path = 0;
	while (envp[++i])
	{
		temp = get_env_var(envp[i]);
		if (!temp[0])
		{
			set_exit_code(1, true);
			return ;
		}
		if (update_env_lst(data, temp))
			return ;
		free_array(temp);
	}
	get_rank(&data->env);
}

int	update_env_lst(t_data *data, char **temp)
{
	if (!temp[1])
	{
		if (ft_lstadd_back(&data->env, ft_lstnew(0,
					ft_strdup(temp[0]))))
		{
			free_list(&data->env);
			ft_putendl_fd("error getting env", STDERR_FILENO);
			return (set_exit_code(1, true));
		}
	}
	else
	{
		if (ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(temp[1]),
					ft_strdup(temp[0]))))
		{
			free_list(&data->env);
			ft_putendl_fd("error getting env", STDERR_FILENO);
			return (set_exit_code(1, true));
		}
	}
	return (0);
}

/* Function to add paths to data structure */
char	**get_paths(t_tokens *envp, char **paths)
{
	t_tokens	*head;
	char		**data_path;
	char		*temp;
	int			i;

	head = envp;
	i = -1;
	if (paths)
		free_array(paths);
	head = get_env_node(envp, "PATH");
	if (!head)
		return (NULL);
	data_path = ft_split(head->content, ':');
	while (data_path[++i])
	{
		temp = data_path[i];
		data_path[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	return (data_path);
}

/* This function ranks the variables alphabetically */
void	get_rank(t_tokens **lst)
{
	t_tokens	*current;
	t_tokens	*head;

	head = *lst;
	reset_rank(lst);
	while (*lst)
	{
		current = head;
		while (current)
		{
			if (ft_strcmp((*lst)->var, current->var) > 0)
				(*lst)->rank++;
			current = current->next;
		}
		*lst = (*lst)->next;
	}
	*lst = head;
	return ;
}

char	**prep_envp(t_tokens *env)
{
	int			i;
	int			n;
	char		*temp;
	char		**envp;

	i = 0;
	n = ft_lstsize(env);
	envp = (char **)ft_calloc(sizeof(char *), (n + 1));
	i = -1;
	while (++i < n)
	{
		temp = ft_strjoin(env->var, "=");
		envp[i] = free_joined(temp, env->content);
		env = env->next;
	}
	return (envp);
}
