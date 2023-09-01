/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:53:31 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/19 10:03:27 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_var(char c, va_list args)
{
	int	i;

	i = 1;
	if (c == 'c')
		ft_putchar(va_arg(args, int));
	else if (c == '%')
		ft_putchar('%');
	else if (c == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
	{
		i = ft_putptr_base(va_arg(args, unsigned long),
				"0123456789abcdef", 0);
	}
	else if (c == 'd' || c == 'i')
		i = ft_putnbr_base(va_arg(args, int), "0123456789", 10);
	else if (c == 'u')
		i = ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10);
	else if (c == 'x')
		i = ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789abcdef", 16);
	else if (c == 'X')
		i = ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		counter;

	va_start(args, s);
	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			counter += check_var(s[i], args);
		}
		else
		{
			ft_putchar(s[i]);
			counter++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}
