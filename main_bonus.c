#include "get_next_line_bonus.h"

int main(void)
{
	int fd1;
	int fd2;
	int fd3;
	char *line;
	char *line2;
	char *line3;
	int i = 0;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	fd3 = open("file3.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("[file1-%d]%s", i, line);
			free(line);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("[file1-%d]%s", i, line2);
			free(line2);
		}
		line3 = get_next_line(fd3);
		if (line3)
		{
			printf("[file1-%d]%s", i, line3);
			free(line3);
		}
		if (!line && !line2 && !line3)
			break ;
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}