/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:07:18 by maghumya          #+#    #+#             */
/*   Updated: 2025/02/02 19:39:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (const char)c)
			return ((char *)s);
		s++;
	}
	if ((const char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s || !*s)
		return (NULL);
	len = ft_strlen(s) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}
