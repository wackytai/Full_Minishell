/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:08:55 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 11:02:50 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_operators(t_tokens *token)
{
	if (!ft_strcmp(token->content, "&&") && !set_exit_code(0, false))
		return (0);
	else if (!ft_strcmp(token->content, "||") && set_exit_code(0, false))
		return (0);
	return (1);
}
