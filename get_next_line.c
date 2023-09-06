/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:56:03 by mkiflema          #+#    #+#             */
/*   Updated: 2023/01/14 12:34:13 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
/*
The get_next_line function reads and returns the next line 
from the specified file descriptor (fd) by utilizing the previously saved buffer.
It also updates the buffer for subsequent calls, making it suitable for sequential line reading operations. 
The usage of static char *saved ensures that the saved buffer retains its state across function calls.
*/
char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	saved = read_and_save(fd, saved);
	if (!saved)
		return (0);
	line = get_line(saved);
	saved = erase_saved_line(saved);
	return (line);
}
