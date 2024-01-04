/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:11:34 by mmoussou          #+#    #+#             */
/*   Updated: 2024/01/04 10:38:08 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (!c)
		return (&((char *)s)[i]);
	return (NULL);
}

void	*ft_calloc(size_t elsize, size_t size)
{
	void	*ptr;

	if (!elsize || !size)
		return (NULL);
	if ((size * elsize) / elsize != size)
		return (NULL);
	ptr = malloc(elsize * size);
	if (!ptr)
		return (NULL);
	while (size--)
		((char *)ptr)[size] = 0;
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = ft_calloc(sizeof(char), 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str [i + j] = s2[j];
	str [i + j] = 0;
	free(s1);
	return (str);
}
