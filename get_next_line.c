/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:07:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/05/17 16:10:27 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *buffer, int fd)
{
	ssize_t	read_size;
	char	*temp;
	char	*line;

	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	read_size = 1;
	while (!ft_strchr(line, '\n') && read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size > 0)
		{
			buffer[read_size] = '\0';
			temp = ft_strjoin(line, buffer);
			free(line);
			line = temp;
			if (!line)
				return (NULL);
		}
	}
	if (!line || !*line || read_size < 0)
		return (free(line), line = NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;

	line = fill_line(buffer, fd);
	if (!line)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	newline = ft_strchr(line, '\n');
	if (newline)
	{
		ft_strlcpy(buffer, newline + 1, ft_strlen(newline + 1) + 1);
		line[newline - line + 1] = '\0';
	}
	else
		buffer[0] = '\0';
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*s;

	s = NULL;
	(void)argc;
	fd = open(argv[1], O_RDONLY);
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	// printf("line: %s", get_next_line(fd));
	do
	{
		free(s);
		s = get_next_line(fd);
		printf("%s", s);
	} while (s);
	return (0);
}
*/