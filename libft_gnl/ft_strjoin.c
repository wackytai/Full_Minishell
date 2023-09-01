/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:00:45 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/09 11:53:11 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	l1;
	size_t	l2;

	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(l1 + l2 + 1);
	if (!str)
		return (NULL);
	while (i < (l1 + l2))
	{
		if (i < l1)
			str[i] = s1[i];
		else
			str[i] = s2[i - l1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
