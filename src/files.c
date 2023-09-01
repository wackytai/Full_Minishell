/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:12:32 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/08/31 14:54:56 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdbool.h>

int	check_files(t_tokens *t, t_cmd *cmd)
{
	while (t && t->type != 2)
	{
		if (t->type < 2)
		{
			if (!ft_strcmp(t->content, "<<") || !ft_strcmp(t->content, "<"))
				check_infile(t, cmd, cmd->rd_in);
			if (cmd->rd_in < 0)
				break ;
			if (cmd->rd_in == -2)
				return (1);
			if (!ft_strcmp(t->content, ">") || !ft_strcmp(t->content, ">>"))
				if (check_outfile(t, cmd) < 0)
					break ;
			t = t->next;
		}
		t = t->next;
	}
	if (cmd->rd_in == -1 || cmd->rd_out == -1)
		return (2);
	return (0);
}

int	check_outfile(t_tokens *t, t_cmd *cmd)
{
	static int	out;
	char		*str;

	out = 0;
	if (out)
		close(out);
	if (!ft_strcmp(t->content, ">"))
		cmd->rd_out = open(t->next->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(t->content, ">>"))
		cmd->rd_out = open(t->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	out = cmd->rd_out;
	if (out < 0)
	{
		if (access(t->next->content, F_OK))
		{
			str = free_joined(ft_strjoin("minishell: ", t->next->content),
					": Permission denied");
			ft_putendl_fd(str, STDERR_FILENO);
			free(str);
		}
		else
			perror("minishell");
	}
	return (out);
}

int	check_infile(t_tokens *t, t_cmd *cmd, int in)
{
	if (!ft_strcmp(t->content, "<"))
	{
		if (in)
			close(in);
		if (access(t->next->content, F_OK))
		{
			cmd->rd_in = -1;
			set_exit_code(1, true);
			perror("minishell");
		}
		else if (access(t->next->content, R_OK))
		{
			cmd->rd_in = -1;
			set_exit_code(126, true);
			perror("minishell");
		}
		else
			cmd->rd_in = open(t->next->content, O_RDONLY);
		in = cmd->rd_in;
	}
	else
		in = handle_here_doc(t, cmd);
	return (in);
}

int	handle_here_doc(t_tokens *t, t_cmd *cmd)
{
	pid_t	pid;
	int		hd_fd;
	int		status;

	hd_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd_fd < 0)
	{
		set_exit_code(126, true);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		set_exit_code(1, true);
		return (-1);
	}
	if (!pid)
		here_doc (t->next->content, hd_fd);
	waitpid(pid, &status, 0);
	signal_intercepter();
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2 && printf("\n"))
		return (-2);
	cmd->rd_in = open("here_doc", R_OK);
	return (cmd->rd_in);
}

int	here_doc(char *limiter, int fd)
{
	char		*line;
	int			len;
	static int	i;

	len = ft_strlen(limiter);
	i = 1;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		i++;
		if (!line)
			print_message(1, limiter, i);
		if (!line || (!ft_strncmp(line, limiter, len) && line[len] == '\n'))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	if (line)
		free(line);
	exit (0);
}
