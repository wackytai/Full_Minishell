/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:13:46 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/10 09:41:58 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while ((s1[i] || s2[i]) && (i < n - 1))
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((const unsigned char) s1[i] - (const unsigned char) s2[i]);
}
