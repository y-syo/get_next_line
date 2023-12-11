/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:23:51 by mmoussou          #+#    #+#             */
/*   Updated: 2023/12/11 10:06:50 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/*char	*get_line(char *stash, char *tmp)
{
	char	*result;

	tmp = ft_strjoin(stash, tmp);
	stash = ft_substr(tmp, ft_strchr(tmp, '\n'), \
			ft_strlen(tmp) - ft_strchr(tmp, '\n'));
	result = ft_substr(tmp, 0, ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	int			n_read;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	n_read = read(fd, tmp, BUFFER_SIZE);
	while (n_read)
	{
		if (ft_strchr(tmp, '\n'))
			return (get_line(stash, tmp));
		stash = ft_strjoin(stash, tmp);
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	return (get_line(stash, tmp));
}*/

char	*get_line(char *tmp, char *line)
{
	char	*newline;

	newline = ft_substr(tmp, 0, ft_strchr(tmp, '\n'));
	free(tmp);
	tmp = ft_strjoin(line, newline);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	char		*line;
	ssize_t		n_read;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	n_read = ft_strlen(stash);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!stash)
		n_read = read(fd, tmp, BUFFER_SIZE);
	line = ft_calloc(sizeof(char), 1);
	if (!line)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ft_strjoin(stash, tmp);
	stash = ft_calloc(sizeof(char), 1);
	if (!stash)
	{
		free(tmp);
		free(line);
		return (NULL);
	}
	while (n_read > 0)
	{
		if (ft_strchr(tmp, '\n'))
		{
			free(stash);
			stash = ft_substr(tmp, ft_strchr(tmp, 10), \
					ft_strlen(tmp) - ft_strchr(tmp, 10));
			return (get_line(tmp, line));
		}
		line = ft_strjoin(line, tmp);
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
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

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close (fd);
}*/

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnlTester/files/41_with_nl", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	close (fd);
}
