/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:27:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/05 14:37:14 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_data *data, t_cmd **cmd, int *i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (!(*cmd)->args[1] && printf("\n") && !set_exit_code(0, true))
		return (1);
	while ((*cmd)->args[++j] && !ft_strcmp((*cmd)->args[j], "-n"))
		flag = 1;
	while ((*cmd)->args[j])
	{
		printf("%s", (*cmd)->args[j++]);
		if ((*cmd)->args[j])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	update_lsts(data, cmd, i);
	set_exit_code(0, true);
	return (1);
}

int	ft_unset(t_data *data, t_cmd **cmd, int *i)
{
	update_lsts(data, cmd, i);
	set_exit_code(0, true);
	return (1);
}

int	ft_export(t_data *data, t_cmd **cmd, int *i)
{
	update_lsts(data, cmd, i);
	set_exit_code(0, true);
	return (1);
}

int	ft_cd(t_data *data, t_cmd **cmd, int *i)
{
	char		*dir;
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
		perror("minishell");
	}
	else
		exit = 0;
	update_dirs(data, dir);
	update_lsts(data, cmd, i);
	set_exit_code(exit, true);
	return (1);
}

char	*check_path(t_tokens *env, t_cmd *cmd)
{
	char	*dir;

	dir = 0;
	if (!cmd->args[1] || (cmd->args[1]
			&& !ft_strcmp(cmd->args[1], "/")))
		dir = env_var(env, "HOME")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "~-"))
		dir = env_var(env, "OLDPWD")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-"))
	{
		dir = env_var(env, "OLDPWD")->content;
		printf("%s\n", dir);
	}
	else if (cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		set_exit_code(1, true);
	}
	else
		dir = cmd->args[1];
	return (dir);
}
