/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:50:53 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 14:04:37 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_in_order(t_tokens **lst, t_tokens *node)
{
	t_tokens	*temp;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	temp = *lst;
	while (temp && ft_strcmp(temp->content, node->content) < 0)
		temp = temp->next;
	node->next = temp;
	if (temp)
	{
		node->prev = temp->prev;
		if (temp->prev)
			temp->prev->next = node;
		temp->prev = node;
	}
	else
	{
		node->prev = ft_lstlast(*lst);
		ft_lstlast(*lst)->next = node;
	}
	*lst = ft_lst_first(node);
}

void	update_lst(t_tokens **node, t_tokens *wc)
{
	t_tokens	*temp;

	temp = *node;
	wc->prev = (*node)->prev;
	if (temp->next)
		temp->next->prev = ft_lstlast(wc);
	ft_lstlast(wc)->next = (*node)->next;
	if (temp->prev)
		temp->prev->next = wc;
	else
		*node = wc;
	temp->next = 0;
	temp->prev = 0;
	free(temp->content);
	free(temp->var);
	free(temp);
	*node = wc;
}

int	check_asterik(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] != '*')
			return (0);
		(*i)++;
	}
	return (1);
}

void	update_values(int *i, int *j, int *last_wc, int *backtrack)
{
	(*j)++;
	*last_wc = *j;
	*backtrack = *i;
}

void	equal_values(int *i, int *j, int *k, int *l)
{
	*i = *j;
	*k = *l;
}
