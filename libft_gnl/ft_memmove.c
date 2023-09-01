/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:19:47 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/09 12:00:06 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*char_dest;
	unsigned char	*char_src;

	i = 0;
	char_dest = (unsigned char *) dest;
	char_src = (unsigned char *) src;
	while (char_src < char_dest && n > 0)
	{
		char_dest[n -1] = char_src[n -1];
		n--;
	}
	while (char_src > char_dest && i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}
