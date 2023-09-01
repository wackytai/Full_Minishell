/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:04 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 14:29:22 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Simple function to print the token list */
void	print_lst(t_tokens *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		printf(" token: %s\n", lst->content);
		i++;
		lst = lst->next;
	}
	return ;
}

/* Function to print environment variables in alphabetical order */
void	print_ordered(t_tokens *lst)
{
	int			i;
	int			size;
	t_tokens	*head;

	i = 0;
	head = lst;
	size = ft_lstsize(lst);
	while (i < size)
	{
		lst = head;
		while (lst)
		{
			if (lst->rank == i)
				printf("%s=%s\n", lst->var, lst->content);
			lst = lst->next;
		}
		i++;
	}
	return ;
}

void	print_message(int flag, char *str, int i)
{
	char	*temp;

	temp = 0;
	if (!flag)
	{
		temp = ft_strjoin(" syntax error near unexpected token `", str);
		temp = free_joined(temp, ft_strdup("'"));
	}
	else if (flag == 1)
	{
		temp = ft_strjoin("warning: here-document at line ", ft_itoa(i));
		temp = free_joined(temp,
				ft_strdup(" delimited by end-of-file (wanted `"));
		temp = free_joined(temp, ft_strdup(str));
		temp = free_joined(temp, ft_strdup("'"));
	}
	ft_putendl_fd(temp, STDERR_FILENO);
	if (temp)
		free(temp);
}

void	forbidden_print(int flag, char *str)
{
	char	*temp;

	temp = 0;
	if (flag == 1)
	{
		temp = ft_strjoin("Forbidden sequence of characters detected: '", str);
		temp = free_joined(temp, "'");
	}
	else if (flag == 2)
	{
		temp = ft_strjoin("Forbidden character detected: '", str);
		temp = free_joined(temp, "'");
	}
	ft_putendl_fd(temp, STDERR_FILENO);
	if (temp)
		free(temp);
}
