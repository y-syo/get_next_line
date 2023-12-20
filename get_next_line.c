/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:23:51 by mmoussou          #+#    #+#             */
/*   Updated: 2023/12/20 13:55:03 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*trim_line(char *stash, char *tmp, char *line)
{
	char	*newline;

	free(stash);
	stash = ft_substr(tmp, ft_strchr(tmp, 10), \
		ft_strlen(tmp) - ft_strchr(tmp, 10));
	if (!stash)
		return (NULL);
	newline = ft_substr(tmp, 0, ft_strchr(tmp, '\n'));
	free(tmp);
	if (!newline)
		return (NULL);
	tmp = ft_strjoin(line, newline);
	return (tmp);
}

char	*last_line(char *stash, char *line)
{
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
	if (!line[0])
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_line(char *stash, char *tmp, int n_read, int fd)
{
	char	*line;

	line = ft_calloc(sizeof(char), 1);
	if (!line)
		free(tmp);
	if (!line)
		return (NULL);
	while (n_read > 0)
	{
		if (ft_strchr(tmp, '\n'))
			return (trim_line(stash, tmp, line));
		line = ft_strjoin(line, tmp);
		if (!line)
			return (NULL);
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!tmp)
			free(line);
		if (!tmp)
			return (NULL);
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	return (last_line(stash, line));
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	ssize_t		n_read;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	n_read = ft_strlen(stash);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!stash)
		n_read = read(fd, tmp, BUFFER_SIZE);
	tmp = ft_strjoin(stash, tmp);
	if (!tmp)
		return (NULL);
	stash = ft_calloc(sizeof(char), 1);
	if (!stash)
	{
		free(tmp);
		return (NULL);
	}
	return (get_line(stash, tmp, n_read, fd));
}
