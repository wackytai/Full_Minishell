/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:22:48 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/15 15:04:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	int			i;
	char		*line;
	static char	stretch[FOPEN_MAX][BUFFER_SIZE + 1];

	i = 1;
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (0);
	line = ft_strjoin_gnl(0, stretch[fd]);
	if (check_stretch(stretch[fd]))
		return (line);
	while (i > 0)
	{
		i = read(fd, stretch[fd], BUFFER_SIZE);
		if (i == -1)
			return (ft_free(line));
		if (i == 0 && line[0] == '\0')
			return (ft_free(line));
		line = ft_strjoin_gnl(line, stretch[fd]);
		if (check_stretch(stretch[fd]))
			break ;
	}
	return (line);
}
