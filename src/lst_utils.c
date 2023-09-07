/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:21:12 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 15:04:15 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Function to create a new node, properly allocating memory to it */
t_tokens	*ft_lstnew(char *content, char *var_name)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
	{
		set_exit_code(1, true);
		return (0);
	}
	new->content = content;
	new->type = -1;
	new->rank = 0;
	new->var = var_name;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/* This function gets the last node from the list */
t_tokens	*ft_lstlast(t_tokens *lst)
{
	if (!lst)
	{
		set_exit_code(1, true);
		return (0);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/* Function to get the size of the list */
int	ft_lstsize(t_tokens *lst)
{
	int	i;

	i = 0;
	if (!lst)
	{
		set_exit_code(1, true);
		return (0);
	}
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/* This function adds a node to the front of the list */
void	ft_lstadd_front(t_tokens **lst, t_tokens *node)
{
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	node->next = *lst;
	*lst = node;
}

/* This function adds a node to the back of the list */
int	ft_lstadd_back(t_tokens **lst, t_tokens *node)
{
	t_tokens	*temp;

	if (!node)
		return (set_exit_code(1, true));
	if (!*lst)
	{
		*lst = node;
		(*lst)->prev = 0;
		return (0);
	}
	temp = ft_lstlast(*lst);
	temp->next = node;
	temp->next->prev = temp;
	return (0);
}
