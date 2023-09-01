/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:32:02 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 16:30:23 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_tokens *token, t_data *data, t_cmd	**cmd, int *i)
{
	if (!ft_strcmp(token->content, "pwd"))
		return (ft_pwd(data, cmd, i));
	else if (!ft_strcmp(token->content, "cd"))
		return (1);
	else if (!ft_strcmp(token->content, "export"))
		return (1);
	else if (!ft_strcmp(token->content, "echo"))
		return (1);
	else if (!ft_strcmp(token->content, "unset"))
		return (1);
	else if (!ft_strcmp(token->content, "env"))
		return (1);
	else if (!ft_strcmp(token->content, "exit"))
	{
		ft_exit(data, cmd, i);
		return (1);
	}
	return (0);
}

int	ft_pwd(t_data *data, t_cmd	**cmd, int *i)
{
	char	*temp;

	temp = 0;
	(*i)++;
	temp = getcwd(temp, 0);
	if (!temp)
	{
		set_exit_code(1, true);
		return (0);
	}
	if ((*cmd)->rd_out != 0)
		ft_putendl_fd(temp, (*cmd)->rd_out);
	else
		ft_putendl_fd(temp, (*cmd)->fd_out);
	free(temp);
	skip_to_pipe(data);
	*cmd = (*cmd)->next;
	set_exit_code(0, true);
	return (1);
}

int	ft_exit(t_data *data, t_cmd **cmd, int *i)
{
	unsigned long long	n;
	int					j;

	n = set_exit_code(0, false);
	j = 0;
	(*i)++;
	skip_to_pipe(data);
	if (!(*cmd)->args[1])
	{
		*cmd = (*cmd)->next;
		return (set_exit_code(0, false));
	}
	else
	{
		while ((*cmd)->args[1][0] == '-' || (*cmd)->args[1][0] == '+'
			|| ft_isdigit((*cmd)->args[1][j]))
			j++;
		if (!(*cmd)->args[1][j])
			n = ft_atoll((*cmd)->args[1]);
		n = 2;
		ft_putendl_fd("minishell: numeric argument required", STDERR_FILENO);
	}
	*cmd = (*cmd)->next;
	return (set_exit_code(n, true));
}
