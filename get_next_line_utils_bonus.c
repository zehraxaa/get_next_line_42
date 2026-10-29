/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 00:19:12 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/30 00:19:54 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*lst_last(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

int	lst_add_back(t_list **list, char *content)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = NULL;
	if (*list == NULL)
	{
		*list = new_node;
		return (1);
	}
	else
	{
		last = lst_last(*list);
		last->next = new_node;
		return (1);
	}
}

// node'u alacak içinde \n var mı diye bakacak. bunu read ile
// okuma yaptığımız döngüde çağırıcaz
int	has_new_line(t_list *list)
{
	t_list	*last;
	int		i;

	last = lst_last(list);
	if (!last)
		return (0);
	i = 0;
	while (last->content[i] != '\0')
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// \n'e kadar olan satırın uzunluğunu hesaplayıp malloc yapmak için
int	line_len(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
				return (len + 1);
			len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}

void	free_list(t_list *list)
{
	t_list	*tmp_next;

	while (list)
	{
		tmp_next = list->next;
		free(list->content);
		free(list);
		list = tmp_next;
	}
}
