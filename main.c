#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char ** argv)
{
	int		fd;
	char	*line;
	(void)argc;

	fd = open(argv[1], O_RDONLY);
	printf("%d", BUFFER_SIZE);
	if (fd < 0)
	{
		printf("File could not opened");
		return 1;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
