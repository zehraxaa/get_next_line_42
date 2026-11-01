#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	// int		fd[MAX_FD];
	// char	*line;

	// fd[0] = open("abc", O_RDONLY);
	// fd[1] = open("main.c", O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("File could not opened");
	// 	return 1;
	// }
	// line = get_next_line(fd[0]);
	// while (line != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd[0]);
	// }
	// line = get_next_line(fd[1]);
	// while (line != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd[1]);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// return (0);

	int		fd1;
	int		fd2;
	char	*line;

	if (argc != 3)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		if (fd1 >= 0)
			close(fd1);
		if (fd2 >= 0)
			close(fd2);
		return (1);
	}
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	close(fd1);
	close(fd2);
	return (0);
}