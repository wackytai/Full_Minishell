/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:09:08 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/10 10:54:58 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nb_length(int n)
{
	int	j;
	int	i;

	j = n;
	i = 0;
	while (j != 0)
	{
		i++;
		j = (j / 10);
	}
	if (n == 0)
		i++;
	if (n < 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	nb;
	char			*s;

	i = 0;
	nb = n;
	i = nb_length(n);
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		nb *= -1;
	}
	s[i--] = '\0';
	while ((nb / 10) > 0)
	{
		s[i] = (nb % 10) + '0';
		nb = (nb / 10);
		i--;
	}
	s[i--] = nb + '0';
	return (s);
}
