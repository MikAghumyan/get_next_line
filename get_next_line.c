/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:07:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/01/31 20:01:02 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
*/
static char	*ft_strfjoin(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s2)
		return (NULL);
	if (!s1)
		len = 0 + ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if(s1)
		ft_strlcpy(res, s1, len + 1);
	ft_strlcat(res, s2, len + 1);
	free((char *)s1);
	return (res);
}

static char *get_line(char *storage, char *line)
{
	char	*endlptr;

	if (!storage)
		return (NULL);
	endlptr = ft_strchr(storage, '\n');
	if (!endlptr)
	{
		line = storage;
		storage = NULL;
		return (NULL);
	}
	line = storage;
	storage = ft_substr(storage, (int)(endlptr - storage) + 1, ft_strlen(endlptr + 1));
	if(!storage)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line[endlptr - line] = '\0';
	// printf("storage:\n%s\nline:\n%s\n", storage, line);
	return (line);
}


static char	*read_file(char *buffer, char *storage, int fd)
{
	int		read_bytes;
	char	*temp;
	//static int k = 1;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = storage;
		storage = ft_strfjoin(temp, buffer);
		if (!storage)
			return (free(temp), temp = NULL, NULL);
		if (ft_strchr(storage, '\n'))
			break;
	}
	//printf("%d\n%s\n", k++, storage);
	/*write(1, storage, 5);*/
	/*printf("%s\n", storage);*/
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*temp;
	static int k = 0;

	temp =  (char *)malloc(BUFFER_SIZE + 1);
	if (!fd || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(temp);
		temp = NULL;
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = read_file(temp, storage, fd);
	if (!storage)
		return (NULL);
	printf("%d:\n %s\n", ++k, storage);
	temp = get_line(storage, temp);
	return (temp);
}

#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	fd;

	// char	*line;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error: Could not open file\n");
			return (1);
		}
		/*line = get_next_line(fd);
		while (line)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}*/
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		//printf("%s\n", get_next_line(fd));
		//printf("%s\n", get_next_line(fd));
		//printf("%s\n", get_next_line(fd));
		//printf("%s\n", get_next_line(fd));
		close(fd);
	}
	else
		printf("Error: Invalid number of arguments\n");
	return (0);
}
