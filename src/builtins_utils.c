/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:32:27 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 16:21:35 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	ft_atoll(char *str)
{
	long long	res;
	int			s;
	int			i;

	res = 0;
	i = 0;
	s = 1;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '+' || str[i] == '-')
			if (str[i++] == '-')
				s *= -1;
		while (str[i] > 47 && str[i] < 58)
		{
			res = (res * 10) + (str[i] - '0');
			i++;
		}
	}
	return (res * s);
}
