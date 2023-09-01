/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:08:06 by marvin            #+#    #+#             */
/*   Updated: 2023/06/19 10:03:12 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_base(unsigned long n, char *base, int j)
{
	int	i;

	i = 0;
	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (j == 0)
	{
		write(1, "0x", 2);
		i += 2;
	}
	if (n / 16 > 0)
		i += ft_putptr_base((n / 16), base, 1);
	ft_putchar(base[n % 16]);
	i++;
	return (i);
}
