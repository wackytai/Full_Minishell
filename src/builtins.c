/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:32:02 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 15:06:43 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_tokens *token, t_data *data, t_cmd	**cmd)
{
	if (!ft_strcmp(token->content, "pwd"))
		return (ft_pwd(data, cmd));
	else if (!ft_strcmp(token->content, "cd"))
		return (printf("cd builtin\n"));
	else if (!ft_strcmp(token->content, "export"))
		return (printf("export builtin\n"));
	else if (!ft_strcmp(token->content, "echo"))
		return (printf("echo builtin\n"));
	else if (!ft_strcmp(token->content, "unset"))
		return (printf("unset builtin\n"));
	else if (!ft_strcmp(token->content, "env"))
		return (printf("env builtin\n"));
	else if (!ft_strcmp(token->content, "exit"))
		return (printf("exit builtin\n"));
	return (0);
}

int	ft_pwd(t_data *data, t_cmd	**cmd)
{
	char	*temp;

	temp = 0;
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
