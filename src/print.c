/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:04 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 15:24:15 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_exp_var(int flag, int out, t_tokens *node)
{
	char	*temp;

	temp = ft_strjoin("declare -x ", node->var);
	if (flag)
	{
		temp = free_joined(temp, ft_strdup("=\""));
		temp = free_joined(temp, ft_strdup(node->content));
		temp = free_joined(temp, ft_strdup("\""));
	}
	ft_putendl_fd(temp, out);
	free(temp);
}

/* Function to print environment variables in alphabetical order */
void	print_ordered(t_tokens *lst, int out)
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
			{
				if (!lst->content)
					print_exp_var(0, out, lst);
				else
					print_exp_var(1, out, lst);
			}
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
		temp = free_joined(temp, ft_strdup("'"));
	}
	else if (flag == 2)
	{
		temp = ft_substr(str, 0, 1);
		temp = free_joined(ft_strdup("Forbidden character detected: '"), temp);
		temp = free_joined(temp, ft_strdup("'"));
	}
	ft_putendl_fd(temp, STDERR_FILENO);
	if (temp)
		free(temp);
}

int	exit_error(char *str)
{
	char	*temp;

	temp = ft_strjoin("exit: ", str);
	temp = free_joined(temp, ft_strdup(": numeric argument required"));
	ft_putendl_fd(temp, STDERR_FILENO);
	free(temp);
	return (1);
}
