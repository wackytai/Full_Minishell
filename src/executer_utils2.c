/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:29:12 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 10:57:24 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_pipes(t_data *data, t_cmd **cmds)
{
	int	n;
	int	i;

	n = count_lst_type(data->tokens, 2) + 1;
	if (n <= 1)
	{
		i = check_builtins(data, cmds);
		if (i)
			free_cmd_lst(cmds);
		return (i);
	}
	else
		return (0);
}
