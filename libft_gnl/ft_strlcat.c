/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:42:08 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/11 11:06:51 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	k;
	size_t	l;

	j = 0;
	k = ft_strlen(src);
	l = ft_strlen(dest);
	if (!dest && !size)
		return (0);
	if (size < l || size == 0)
	{
		return (k + size);
	}
	while (src[j] && (l + j) < size - 1)
	{
		dest[l + j] = src[j];
		j++;
	}
	dest[l + j] = '\0';
	return (l + k);
}
