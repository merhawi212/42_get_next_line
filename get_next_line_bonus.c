/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:23:28 by mkiflema          #+#    #+#             */
/*   Updated: 2023/01/25 21:03:59 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
This function removes the current line from a saved buffer and 
returns the remaining content as a new string. It uses the variable i
to locate the newline character ('\n') in the saved buffer, 
and then allocates memory for the new string with a size of ft_strlen(saved) - i + 1 characters.
The +1 accounts for the null terminator at the end of the string.
*/
char	*erase_saved_line(char *saved)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (free(saved), NULL);
	next = malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		next[j++] = saved[i++];
	next[j] = '\0';
	free(saved);
	return (next);
}

/*
The get_line function extracts and returns a line from the saved buffer, 
including the newline character if present. It uses the variable i to 
find the newline character ('\n') or the end of the saved buffer.
The allocated memory for the line is of size i + 2,
where +2 accommodates the newline character and the null terminator.
*/
char	*get_line(char *saved)
{
	char	*line;
	int		i;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (saved[++i]  && saved[i] != '\n')
		line[i] = saved[i];
	if (saved[i] == '\n')
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
This function reads data from a file descriptor (fd) and 
appends it to the saved buffer until a newline character is encountered 
or the end of the file is reached. It ensures that the 
saved buffer always contains enough data for line-by-line reading.
*/
char	*read_and_save(int fd, char *saved)
{
	char	*buff;
	int		readed_bytes;

	buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed_bytes = 1;
	while (!(ft_strchr(saved, '\n')) && readed_bytes > 0)
	{
		readed_bytes = read(fd, buff, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (free(buff), NULL);
		buff[readed_bytes] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved[256];
	char		*line;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	saved[fd] = read_and_save(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = get_line(saved[fd]);
	saved[fd] = erase_saved_line(saved[fd]);
	return (line);
}
