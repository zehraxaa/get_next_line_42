#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main()
{
	t_list *list = NULL;

	lst_add_back(&list, "abc");
	lst_add_back(&list, "def");
	lst_add_back(&list, "ghi");

	printf("AL sana content: %s\n", lst_last(list)->content);
}