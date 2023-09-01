/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:48:58 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/14 09:08:04 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_mem(char **res, int k)
{
	while (k)
	{
		free(res[k]);
		k--;
	}
	free(res);
	return (0);
}

static char	**create_substr(char **res, char const *s, char c, int i)
{
	int	j;
	int	k;

	k = -1;
	while (++k < i)
	{
		j = 0;
		while (*s == c)
			s++;
		while (s[j] != c && s[j])
			j++;
		if (((s[j] == c) || s[j] == 0) && s[j - 1] != c)
		{
			res[k] = ft_substr(s, 0, j);
			if (!res[k])
				free_mem(res, k);
		}
		s = s + j;
	}
	res[k] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (s[0] != c && s[0] != '\0')
		i++;
	while (s[j])
	{
		if ((s[j] == c && s[j + 1] != c) && s[j + 1])
			i++;
		j++;
	}
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		return (0);
	res = create_substr(res, s, c, i);
	return (res);
}
