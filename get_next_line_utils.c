/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:09:55 by mmoussou          #+#    #+#             */
/*   Updated: 2023/12/16 15:08:42 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	size_t	nl;
	char	*r;

	if (!s || !len)
		return (NULL);
	l = ft_strlen(s);
	if (start > l)
		return (NULL);
	nl = ft_strlen(s + start);
	if (nl > len)
		nl = len;
	r = ft_calloc(sizeof(char), nl + 1);
	if (!r)
		return (NULL);
	while (nl--)
		r[nl] = s[start + nl];
	return (r);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	*ft_strjoin(char *s1, char *s2)
{
	char	*fstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_calloc(sizeof(char), 2);
	if (!s2)
		s2 = ft_calloc(sizeof(char), 2);
	fstr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!fstr)
		return (NULL);
	while (s1[i])
	{
		fstr[i] = s1[i];
		i++;
	}
	free(s1);
	s1 = NULL;
	while (s2[j++])
		fstr[i + j - 1] = s2[j - 1];
	free(s2);
	s2 = NULL;
	return (fstr);
}
