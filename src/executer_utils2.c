/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:29:12 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/18 11:59:31 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_pipes(t_data *data, t_cmd **cmds)
{
	int	n;
	int	i;
	int	check;

	n = count_lst_type(data->tokens, 2);
	if (!n && ft_isbuiltin((*cmds)->args[0]))
	{
		check = check_files(data->tokens, *cmds, data);
		if (check && check != 1)
			(*cmds)->rd_in = -1;
		if (check == 1)
			return (set_exit_code(1, true));
		check_fds(*cmds, 0);
		i = check_builtins(data, cmds);
		if (i)
			free_cmd_lst(cmds);
		return (i);
	}
	else
		return (0);
}
