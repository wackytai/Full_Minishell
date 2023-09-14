/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:32:02 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/14 14:18:53 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_data *data, t_cmd	**cmd)
{
	int	out;

	out = STDOUT_FILENO;
	if (!(*cmd)->next && !(*cmd)->prev)
		out = (*cmd)->fd_out;
	if (!ft_strcmp((*cmd)->args[0], "pwd"))
		return (ft_pwd(out));
	else if (!ft_strcmp((*cmd)->args[0], "cd"))
		return (ft_cd(data, cmd));
	else if (!ft_strcmp((*cmd)->args[0], "export"))
		return (ft_export(data, cmd, out));
	else if (!ft_strcmp((*cmd)->args[0], "echo"))
		return (ft_echo(cmd, out));
	else if (!ft_strcmp((*cmd)->args[0], "unset"))
		return (ft_unset(data, cmd));
	else if (!ft_strcmp((*cmd)->args[0], "env"))
		return (ft_env(data, out));
	else if (!ft_strcmp((*cmd)->args[0], "exit"))
	{
		ft_putendl_fd("exit", out);
		ft_exit(data, cmd);
		return (1);
	}
	return (0);
}

int	update_lsts(t_data *data, int *i)
{
	(*i)++;
	skip_to_pipe(data);
	return (1);
}

int	ft_pwd(int out)
{
	char	*temp;

	temp = 0;
	temp = getcwd(temp, 0);
	if (!temp)
	{
		set_exit_code(1, true);
		return (0);
	}
	ft_putendl_fd(temp, out);
	free(temp);
	set_exit_code(0, true);
	return (1);
}

int	ft_exit(t_data *data, t_cmd **cmd)
{
	int	n;
	int	j;

	n = set_exit_code(0, false);
	j = 0;
	if (!(*cmd)->args[1] && free_all(0, data, cmd, 1))
		exit (set_exit_code(0, false));
	else
	{
		if ((*cmd)->args[2] && !check_exit_arg((*cmd)->args[1]))
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			free_all(0, data, cmd, 1);
			return (set_exit_code(1, true));
		}
		if (check_exit_arg((*cmd)->args[1]) && free_all(0, data, cmd, 1))
			return (set_exit_code(2, true));
		n = check_number((*cmd)->args[1]);
	}
	free_all(0, data, cmd, 1);
	exit (set_exit_code(n, true));
}

int	ft_env(t_data *data, int out)
{
	t_tokens	*envp;

	envp = data->env;
	while (envp)
	{
		if (envp->content)
		{
			ft_putstr_fd(envp->var, out);
			ft_putstr_fd("=", out);
			ft_putendl_fd(envp->content, out);
		}
		envp = envp->next;
	}
	set_exit_code(0, true);
	return (1);
}
