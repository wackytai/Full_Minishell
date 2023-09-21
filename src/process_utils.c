/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:09:29 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/21 09:44:47 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_pids(t_data *data)
{
	int	i;
	int	n;

	i = -1;
	n = count_lst_type(data->tokens, 2) + 1;
	data->pid = (pid_t *)malloc(sizeof(pid_t) * n);
	if (!data->pid)
		return (set_exit_code(1, true));
	while (++i < n)
		data->pid[i] = -1;
	return (0);
}

int	update_io(t_data *data, t_cmd *cmds, int pipe_fd[2])
{
	if (cmds->fd_in)
	{	
		if (dup2(cmds->fd_in, STDIN_FILENO) < 0)
		{
			free_all(0, data, &cmds, 1);
			exit(set_exit_code(1, true));
		}
	}
	if (cmds->fd_out != 1)
	{
		if (dup2(cmds->fd_out, STDOUT_FILENO) < 0)
		{
			free_all(0, data, &cmds, 1);
			exit(set_exit_code(1, true));
		}
	}
	if (pipe_fd && pipe_fd[0])
		close(pipe_fd[0]);
	if (cmds->fd_in > 2)
		close(cmds->fd_in);
	if (cmds->fd_out > 2)
		close(cmds->fd_out);
	return (0);
}

int	check_fds(t_cmd *cmds, int pipe[2])
{
	if (!cmds->prev)
	{
		if (cmds->next)
			cmds->fd_out = pipe[1];
		else
			cmds->fd_out = STDOUT_FILENO;
	}
	else if (!cmds->next)
		cmds->fd_out = STDOUT_FILENO;
	else
		cmds->fd_out = pipe[1];
	if (cmds->rd_in > 0 || cmds->rd_in == -1)
		cmds->fd_in = cmds->rd_in;
	if (cmds->rd_out > 0 || cmds->rd_out == -1)
		cmds->fd_out = cmds->rd_out;
	return (0);
}

int	handle_pipeline(t_data *data, t_cmd **cmds, int i)
{
	check_fds(*cmds, data->pipe_fd);
	child_signal_intercepter();
	data->pid[i] = fork();
	if (data->pid[i] < 0)
		return (1);
	if (!data->pid[i])
	{
		update_io(data, (*cmds), data->pipe_fd);
		if (check_builtins(data, cmds))
		{
			free_all(0, data, cmds, 1);
			exit(set_exit_code(0, false));
		}
		exe_cmd(data, cmds);
	}
	update_lsts(data, &i);
	if ((*cmds)->fd_in > 2)
		close((*cmds)->fd_in);
	if ((*cmds)->fd_out > 2)
		close((*cmds)->fd_out);
	return (0);
}

int	wait_processes(t_data *data)
{
	int	status;
	int	i;
	int	n;

	i = -1;
	status = 0;
	n = count_lst_type(data->tokens, 2) + 1;
	while (++i < n)
		waitpid(data->pid[i], &status, 0);
	signal_intercepter();
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
