/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:27:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/08 12:02:37 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_cmd **cmd, int out)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if ((*cmd)->fd_in < 0)
		return (set_exit_code(1, true));
	if (!(*cmd)->args[1] && !set_exit_code(0, true))
	{
		ft_putstr_fd("\n", (*cmd)->fd_out);
		return (1);
	}
	while ((*cmd)->args[++j] && !ft_strcmp((*cmd)->args[j], "-n"))
		flag = 1;
	while ((*cmd)->args[j])
	{
		ft_putstr_fd((*cmd)->args[j++], out);
		if ((*cmd)->args[j])
			ft_putstr_fd(" ", out);
	}
	if (!flag)
		ft_putstr_fd("\n", out);
	set_exit_code(0, true);
	return (1);
}

int	ft_unset(t_data *data, t_cmd **cmd)
{
	int			j;
	int			exit;

	j = 0;
	exit = 0;
	if (!(*cmd)->args[1])
	{
		set_exit_code(exit, true);
		return (1);
	}
	exit = unset_var(data, *cmd);
	set_exit_code(exit, true);
	return (1);
}

int	ft_export(t_data *data, t_cmd **cmd, int out)
{
	int	exit;

	exit = 0;
	if (!(*cmd)->args[1])
		print_ordered(data->env, out);
	else
		exit = create_export_var(*cmd, &data->env);
	set_exit_code(exit, true);
	return (1);
}

int	ft_cd(t_data *data, t_cmd **cmd)
{
	char		*dir;
	char		*temp;
	int			exit;

	dir = 0;
	dir = check_path(data->env, *cmd);
	if (!dir)
		return (1);
	exit = chdir(dir);
	if (exit)
	{
		dir = 0;
		exit = 1;
		temp = ft_strjoin("cd: ", (*cmd)->args[1]);
		perror(temp);
		free(temp);
	}
	else
		update_dirs(data, dir);
	set_exit_code(exit, true);
	return (1);
}

char	*check_path(t_tokens *env, t_cmd *cmd)
{
	char	*dir;

	dir = 0;
	if (!cmd->args[1] || (cmd->args[1]
			&& (!ft_strcmp(cmd->args[1], "/")
				|| !ft_strcmp(cmd->args[1], "~"))))
		dir = get_env_node(env, "HOME")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "~-"))
		dir = get_env_node(env, "OLDPWD")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-"))
	{
		dir = get_env_node(env, "OLDPWD")->content;
		ft_putendl_fd(dir, cmd->fd_out);
	}
	else if (cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		set_exit_code(1, true);
	}
	else
		dir = cmd->args[1];
	return (dir);
}
