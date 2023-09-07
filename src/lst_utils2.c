/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:07:39 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 15:04:59 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_lst_type(t_tokens *tokens, int type)
{
	int			i;
	int			flag;
	t_tokens	*lst;

	i = 0;
	flag = 0;
	lst = tokens;
	while (lst)
	{
		if (type == 2 && lst->content[0] == '(')
			flag++;
		else if (type == 2 && lst->content[0] == ')')
			flag--;
		if (lst->type == type && !flag)
			i++;
		lst = lst->next;
	}
	return (i);
}

t_cmd	*ft_cmdnew(char **cmds)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		set_exit_code(1, true);
		return (0);
	}
	new->next = NULL;
	new->prev = NULL;
	new->cmd_path = 0;
	new->args = cmds;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->rd_in = 0;
	new->rd_out = 0;
	return (new);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
	{
		set_exit_code(1, true);
		return (0);
	}
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd	**lst, t_cmd *node)
{
	t_cmd	*temp;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	temp = cmd_last(*lst);
	temp->next = node;
	temp->next->prev = temp;
	return ;
}

t_tokens	*ft_lst_first(t_tokens *lst)
{
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
