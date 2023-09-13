/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:19:52 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:05:10 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Functions to deal with CTRL-C and CTRL-D */
void	signal_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	set_exit_code(130, true);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	signal_intercepter(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_code(130, true);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
	return ;
}

void	child_signal_intercepter(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	return ;
}

int	set_exit_code(int i, bool flag)
{
	static int	code;

	if (flag)
		code = i;
	return (code);
}
