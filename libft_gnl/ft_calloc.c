/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:09:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/15 10:54:10 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	n;
	char	*s;

	i = 0;
	n = nmemb * size;
	s = malloc(n);
	if (!s)
		return (NULL);
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}
