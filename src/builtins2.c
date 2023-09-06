/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:27:01 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/06 16:49:37 by tlemos-m         ###   ########.fr       */
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
	update_lsts(data, i);
	set_exit_code(0, true);
	return (1);
}

int	ft_unset(t_data *data, t_cmd **cmd, int *i)
{
	int			j;
	int			exit;
	int			flag;

	j = 0;
	exit = 0;
	flag = 0;
	if (!(*cmd)->args[1])
	{
		set_exit_code(exit, true);
		return (1);
	}
	while ((*cmd)->args[++j])
	{
		flag = validate_var_name((*cmd)->args[j]);
		if (flag && unset_error((*cmd)->args[j]))
		{
			exit = 1;
			continue ;
		}
		exit = remove_env_node(&data->env, (*cmd)->args[j]);
	}
	i = 0;
	if (flag)
		exit = flag;
	update_lsts(data, i);
	set_exit_code(exit, true);
	return (1);
}

int	ft_export(t_data *data, t_cmd **cmd, int *i)
{
	int	exit;

	exit = 0;
	printf("size 0: %i\n", ft_lstsize(data->env));
	if (!(*cmd)->args[1])
		print_ordered(data->env);
	else
		exit = create_export_var(*cmd, &data->env);
	printf("size 1: %i\n", ft_lstsize(data->env));
	update_lsts(data, i);
	set_exit_code(exit, true);
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
		update_dirs(data, dir);
	update_lsts(data, i);
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
