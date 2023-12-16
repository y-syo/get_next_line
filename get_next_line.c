/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:23:51 by mmoussou          #+#    #+#             */
/*   Updated: 2023/12/16 16:38:24 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*trim_line(char *tmp, char *line)
{
	char	*newline;

	newline = ft_substr(tmp, 0, ft_strchr(tmp, '\n'));
	free(tmp);
	tmp = ft_strjoin(line, newline);
	return (tmp);
}

char	*last_line(char **stash, char *line, int fd)
{
	if (stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	if (!line[0])
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_line(char **stash, char *tmp, int n_read, int fd)
{
	char	*line;

	line = ft_calloc(sizeof(char), 1);
	if (!line)
	{
		free(tmp);
		return (NULL);
	}
	while (n_read > 0)
	{
		if (ft_strchr(tmp, '\n'))
		{
			free(stash[fd]);
			stash[fd] = ft_substr(tmp, ft_strchr(tmp, 10), \
					ft_strlen(tmp) - ft_strchr(tmp, 10));
			return (trim_line(tmp, line));
		}
		line = ft_strjoin(line, tmp);
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		n_read = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	last_line(stash, line, fd);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024] = {NULL};
	char		*tmp;
	char		*line;
	ssize_t		n_read;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	n_read = ft_strlen(stash[fd]);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!stash[fd])
		n_read = read(fd, tmp, BUFFER_SIZE);
	tmp = ft_strjoin(stash[fd], tmp);
	stash[fd] = ft_calloc(sizeof(char), 1);
	if (!stash[fd])
	{
		free(tmp);
		return (NULL);
	}
	tmp = get_line(stash, tmp, n_read, fd);
	return (tmp);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close (fd);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	line = get_next_line(fd);
	printf("1: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("2: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("3: %s", line);
	free(line);
	close (fd);
}*/
