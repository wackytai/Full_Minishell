/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:32:27 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/05 10:19:16 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned char	ft_atoll(char *str)
{
	unsigned long long	res;
	int					s;
	int					i;

	res = 0;
	i = 0;
	s = 1;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			if (str[i++] == '-')
				s *= -1;
		while (str[i] > 47 && str[i] < 58)
		{
			res = (res * 10) + (str[i] - '0');
			i++;
		}
	}
	if (((res - 1) > LLONG_MAX && s < 0) || (res > LLONG_MAX && s > 0))
		res = 2;
	return ((unsigned char)((long long)res * s));
}

int	check_exit_arg(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
	{
		temp = ft_strjoin("minishell: exit: ", str);
		temp = free_joined(temp, ft_strdup(": numeric argument required"));
		ft_putendl_fd(temp, STDERR_FILENO);
		free(temp);
		return (1);
	}
	return (0);
}
