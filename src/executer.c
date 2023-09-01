/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:31:05 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 16:12:56 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	executer(t_data *data)
{
	int			i;
	int			n;
	t_tokens	*t;
	t_cmd		*cmds;
	t_cmd		*head;

	i = -1;
	cmds = 0;
	t = data->tokens;
	n = count_lst_type(data->tokens, 2) + 1;
	if (update_cmd_lst(data->tokens, &cmds, n))
		return (1);
	head = cmds;
	init_pids(data);
	if (exe_tokens(data, &cmds, n))
		return (free_cmd_lst(&head));
	data->tokens = t;
	if (set_exit_code(1, false) && *data->pid == -1)
	{
		free_all(0, data, &head);
		return (0);
	}
	set_exit_code(wait_processes(data), true);
	free_all(0, data, &head);
	return (0);
}

int	exe_tokens(t_data *data, t_cmd **cmd, int n)
{
	int	i;
	int	check;

	i = -1;
	while (data->tokens && cmd)
	{
		if (!data->tokens->content[0])
		{
			data->tokens = data->tokens->next;
			continue ;
		}
		check = check_files(data->tokens, *cmd);
		if (check == 1)
			return (1);
		jump_tokens(data);
		if (check)
			(*cmd)->rd_in = -1;
		if (data->tokens && data->tokens->type == 6
			&& !check_builtins(data->tokens, data, cmd, &i))
			if (forking(data, cmd, ++i, n))
				return (set_exit_code(0, false));
		if (data->tokens)
			data->tokens = data->tokens->next;
	}
	return (0);
}

int	update_cmd_lst(t_tokens *tokens, t_cmd **cmd, int i)
{
	while (--i > -1)
	{
		if (!tokens->content[0])
			tokens = tokens->next;
		if (tokens && get_cmd_lst(tokens, cmd))
			return (1);
		while (tokens)
		{
			tokens = tokens->next;
			if (!tokens || (tokens && tokens->prev->type == 2))
				break ;
		}
	}
	return (0);
}

int	forking(t_data *data, t_cmd **cmds, int i, int n)
{
	int	pipe_fd[2];

	if (n < 2)
	{
		check_fds(*cmds, 0);
		child_signal_intercepter();
		data->pid[i] = fork();
		if (!data->pid[i])
		{
			update_io(*cmds, 0);
			exe_cmd(data, cmds);
		}
		if ((*cmds)->fd_in > 2)
			close((*cmds)->fd_in);
		if ((*cmds)->fd_out > 2)
			close((*cmds)->fd_out);
	}
	else
		if (handle_pipeline(data, cmds, i, pipe_fd))
			return (set_exit_code(1, true));
	skip_to_pipe(data);
	if ((*cmds)->next && data->tokens->next)
		(*cmds)->next->fd_in = pipe_fd[0];
	*cmds = (*cmds)->next;
	return (0);
}

void	skip_to_pipe(t_data *data)
{
	while (data->tokens->next && data->tokens->next->type != 2)
		data->tokens = data->tokens->next;
}
