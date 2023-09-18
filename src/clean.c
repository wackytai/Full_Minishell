/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:31:04 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/18 12:01:36 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This function frees everything */
int	free_all(char *str, t_data *data, t_cmd **cmds, int flag)
{
	while (cmds && (*cmds)->prev)
		*cmds = (*cmds)->prev;
	if (cmds)
		free_cmd_lst(cmds);
	if (str)
		free(str);
	if (data && data->tokens)
	{
		free_list(&data->tokens);
		data->tokens = 0;
	}
	if (data && data->env && flag)
		if (free_list(&data->env))
			data->env = 0;
	if (data && data->path && flag)
		if (free_array(data->path))
			data->path = 0;
	if (data && data->pid && flag)
	{
		free(data->pid);
		data->pid = 0;
	}
	return (1);
}

/* Function to free a 2D array */
int	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (1);
	while (array[++i])
		free(array[i]);
	free(array);
	array = 0;
	return (1);
}

/* This function frees linked list */
int	free_list(t_tokens **lst)
{
	t_tokens	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		temp->next = 0;
		if (temp->content)
			free(temp->content);
		free(temp->var);
		free(temp);
	}
	lst = 0;
	return (1);
}

/* Function to free and join strings together */
char	*free_joined(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
}

int	free_cmd_lst(t_cmd **lst)
{
	t_cmd	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->cmd_path)
			free(temp->cmd_path);
		free_array(temp->args);
		temp->prev = 0;
		temp->next = 0;
		free(temp);
	}
	lst = 0;
	return (1);
}
