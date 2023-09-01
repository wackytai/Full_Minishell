/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:23:04 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/31 12:48:44 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0' && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1));
	if (!str)
		return (0);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\n' && s2[j])
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = s2[j];
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*ft_free(char *s)
{
	free(s);
	return (0);
}

int	check_stretch(char *stretch)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (stretch[i] && stretch)
	{
		if (flag > 0)
			stretch[j++] = stretch[i];
		if (stretch[i] == '\n')
			flag = 1;
		stretch[i] = '\0';
		i++;
	}
	return (flag);
}
