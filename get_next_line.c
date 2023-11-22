/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:23:51 by mmoussou          #+#    #+#             */
/*   Updated: 2023/11/22 23:37:01 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	char		*line;
	size_t		n_read;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	n_read = read(fd, tmp, BUFFER_SIZE);
	tmp = ft_strjoin(stash, tmp);
	while (n_read)
	{
		if (ft_strchr(tmp, '\n'))
		{
			stash = ft_substr(tmp, ft_strchr(tmp, '\n'), \
					ft_strlen(tmp) - ft_strchr(tmp, '\n'));
			tmp = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - 1);
			return (ft_strjoin(line, tmp));
		}
		line = ft_strjoin(line, ft_substr(tmp, 0, ft_strlen(tmp)));
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	return (tmp);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
}
