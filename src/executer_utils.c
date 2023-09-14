/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:10:32 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/14 12:40:28 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exe_cmd(t_data *data, t_cmd **c)
{
	char		**envp;
	int			exit_code;

	exit_code = 0;
	if (!check_directory((*c)->args[0], 0))
		exit_code = check_exit_code((*c)->args[0], ": Is a directory", 126);
	else if ((((*c)->args[0][0] == '.' || (*c)->args[0][0] == '/'
		|| !ft_strncmp((*c)->args[0], "./", 2))
		&& access((*c)->args[0], F_OK)))
		exit_code = check_exit_code((*c)->args[0],
				": No such file or directory", 127);
	else if (((*c)->args[0][0] == '.' || !ft_strncmp((*c)->args[0], "./", 2))
		&& access((*c)->args[0], X_OK))
		exit_code = check_exit_code((*c)->args[0], ": Permission denied", 126);
	else if (check_cmd(data->path, c))
		exit_code = 127;
	if (exit_code)
	{
		free_all(0, data, c, 1);
		exit(exit_code);
	}
	envp = prep_envp(data->env);
	execve((*c)->cmd_path, (*c)->args, envp);
	free_all(0, data, c, 1);
	exit(1);
}

int	get_cmd_lst(t_tokens *t, t_cmd **cmds)
{
	t_cmd	*node;

	node = ft_cmdnew(get_cmd_args(t));
	if (!node)
	{
		free_cmd_lst(cmds);
		return (set_exit_code(1, true));
	}
	cmd_add_back(cmds, node);
	return (0);
}

void	jump_tokens(t_data *data)
{
	while (data->tokens && (data->tokens->type < 2
			|| (data->tokens->type > 3 && data->tokens->type < 6)))
		data->tokens = data->tokens->next;
}

int	check_directory(char *str, int flag)
{
	DIR	*dirp;

	if (flag || str[0] == '.' || (!ft_strncmp(str, "./", 2) || str[0] == '/'))
	{
		dirp = opendir(str);
		if (!dirp)
			return (1);
		closedir(dirp);
		return (0);
	}
	return (1);
}

int	check_exit_code(char *s1, char *s2, int flag)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	ft_putendl_fd(str, STDERR_FILENO);
	free(str);
	return (flag);
}
