/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:28:19 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:29:25 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*is_command(char **paths, char *cmd)
{
	int		i;
	char	*temp;

	i = -1;
	temp = 0;
	if (!check_directory(cmd, 1)
		&& check_exit_code(cmd, ": command not found", 127))
		return (0);
	while (paths && paths[++i])
	{
		if (!access(cmd, X_OK))
		{
			temp = ft_strdup(cmd);
			return (temp);
		}
		temp = ft_strjoin(paths[i], cmd);
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
	}
	if (!paths)
		check_exit_code(cmd, ": No such file or directory", 127);
	else
		check_exit_code(cmd, ": command not found", 127);
	return (0);
}

int	check_cmd(char **paths, t_cmd **cmd)
{
	char	*test;

	test = is_command(paths, (*cmd)->args[0]);
	if (!test)
		return (1);
	else
	{
		(*cmd)->cmd_path = test;
		return (0);
	}
}

int	cmd_size(t_tokens *tokens)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tokens && (tokens->type != 2 || (tokens->type == 2 && flag)))
	{
		if (!ft_strcmp(tokens->content, "("))
			flag++;
		else if (!ft_strcmp(tokens->content, ")"))
			flag--;
		if (tokens->type > 5 || tokens->type == 3)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

char	**get_cmd_args(t_tokens *t)
{
	int		i;
	char	**cmds;

	i = cmd_size(t);
	cmds = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmds)
	{
		set_exit_code(1, true);
		return (0);
	}
	cmds[i] = 0;
	i = -1;
	while (t && t->type != 2)
	{
		if (t->type > 5 || t->type == 3)
		{
			cmds[++i] = ft_strdup(t->content);
		}
		t = t->next;
	}
	return (cmds);
}
