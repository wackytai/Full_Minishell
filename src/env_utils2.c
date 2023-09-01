/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:29:15 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/08/29 11:05:35 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env_var(char *var)
{
	char	**temp;
	int		i;

	i = -1;
	temp = (char **)malloc(sizeof(char *) * 3);
	temp[2] = 0;
	while (var[++i] && var[i] != '=')
		continue ;
	temp[0] = ft_substr(var, 0, i);
	temp[1] = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	return (temp);
}
