/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:27:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 11:09:43 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_cmd **cmd)
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

int	ft_export(t_data *data, t_cmd **cmd)
{
	int	exit;

	exit = 0;
	if (!(*cmd)->args[1])
		print_ordered(data->env);
	else
		exit = create_export_var(*cmd, &data->env);
	set_exit_code(exit, true);
	return (1);
}

int	ft_cd(t_data *data, t_cmd **cmd)
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
		update_dirs(data, dir);
	set_exit_code(exit, true);
	return (1);
}

char	*check_path(t_tokens *env, t_cmd *cmd)
{
	char	*dir;

	dir = 0;
	if (!cmd->args[1] || (cmd->args[1]
			&& !ft_strcmp(cmd->args[1], "/")))
		dir = get_env_node(env, "HOME")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "~-"))
		dir = get_env_node(env, "OLDPWD")->content;
	else if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-"))
	{
		dir = get_env_node(env, "OLDPWD")->content;
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
