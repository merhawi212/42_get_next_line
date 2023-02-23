#include "get_next_line.h"

#include <stdio.h>

int main(void)
{
	int		fd1;
	char	*line;

	//fd1 = open("file1.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	//close(fd1);
	return (0);
}