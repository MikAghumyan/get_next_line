/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:07:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/02/02 21:26:57 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cut_line(char *line)
{
	size_t	i;
	char	*cut_buff;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i] || !line[i + 1])
		return (NULL);
	cut_buff = ft_strdup(&(line[i + 1]));
	if (!cut_buff)
		return (NULL);
	line[i + 1] = '\0';
	if (!(*cut_buff))
		cut_buff = NULL;
	return (cut_buff);
}

static char	*read_file(char *buffer, char *storage, int fd)
{
	ssize_t	read_bytes;
	char	*temp;

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
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*temp;
	char		*line;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(temp);
		temp = NULL;
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = read_file(temp, storage, fd);
	free(temp);
	if (!line || !(*line))
	{
		return (free(line), NULL);
	}
	storage = cut_line(line);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error: Could not open file\n");
			return (1);
		}
		line = get_next_line(fd);
		// while (line)
		// {
		// 	printf("%s", line);
		// 	free(line);
		// 	line = get_next_line(fd);
		// }
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		get_next_line(fd);
		// printf("%s\n", get_next_line(fd));
		// printf("%s\n", get_next_line(fd));
		// printf("%s\n", get_next_line(fd));
		// printf("%s\n", get_next_line(fd));
		close(fd);
	}
	else
		printf("Error: Invalid number of arguments\n");
	return (0);
}
*/