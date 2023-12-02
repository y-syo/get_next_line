/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:23:51 by mmoussou          #+#    #+#             */
/*   Updated: 2023/12/02 00:27:05 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *tmp, char *line)
{
	tmp = ft_substr(tmp, 0, ft_strchr(tmp, '\n'));
	tmp = ft_strjoin(line, tmp);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	char		*line;
	size_t		n_read;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!stash)
		n_read = read(fd, tmp, BUFFER_SIZE);
	line = ft_calloc(sizeof(char), 1);
	if (!line)
		return (NULL);
	tmp = ft_strjoin(stash, tmp);
	while (n_read)
	{
		if (ft_strchr(tmp, '\n'))
		{
			stash = ft_substr(tmp, ft_strchr(tmp, 10), \
					ft_strlen(tmp) - ft_strchr(tmp, 10));
			return (get_line(tmp, line));
		}
		line = ft_strjoin(line, ft_substr(tmp, 0, ft_strlen(tmp)));
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	if (stash)
	{
		free(stash);
		stash = NULL;
		if (!line[0])
			return (NULL);
	}
	return (line);
}
