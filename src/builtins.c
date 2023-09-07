/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:32:02 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 10:48:20 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_data *data, t_cmd	**cmd)
{
	if (!ft_strcmp(data->tokens->content, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(data->tokens->content, "cd"))
		return (ft_cd(data, cmd));
	else if (!ft_strcmp(data->tokens->content, "export"))
		return (ft_export(data, cmd));
	else if (!ft_strcmp(data->tokens->content, "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(data->tokens->content, "unset"))
		return (ft_unset(data, cmd));
	else if (!ft_strcmp(data->tokens->content, "env"))
		return (ft_env(data));
	else if (!ft_strcmp(data->tokens->content, "exit"))
	{
		ft_putendl_fd("exit", (*cmd)->fd_out);
		ft_exit(cmd);
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

int	ft_pwd(void)
{
	char	*temp;

	temp = 0;
	temp = getcwd(temp, 0);
	if (!temp)
	{
		set_exit_code(1, true);
		return (0);
	}
	ft_putendl_fd(temp, STDOUT_FILENO);
	free(temp);
	set_exit_code(0, true);
	return (1);
}

int	ft_exit(t_cmd **cmd)
{
	int	n;
	int	j;

	n = set_exit_code(0, false);
	j = 0;
	if (!(*cmd)->args[1])
		exit (set_exit_code(0, false));
	else
	{
		if ((*cmd)->args[2] && !check_exit_arg((*cmd)->args[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (set_exit_code(1, true));
		}
		if (check_exit_arg((*cmd)->args[1]))
			return (set_exit_code(2, true));
		n = check_number((*cmd)->args[1]);
	}
	exit (set_exit_code(n, true));
}

int	ft_env(t_data *data)
{
	t_tokens	*envp;

	envp = data->env;
	while (envp)
	{
		if (envp->content)
			printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
	set_exit_code(0, true);
	return (1);
}
