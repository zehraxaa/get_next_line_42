/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:31:24 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/19 14:31:25 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list *lst_last(t_list *list) {
  if (!list)
    return (NULL);
  while (list->next != NULL)
    list = list->next;
  return list;
}

int lst_add_back(t_list **list, char *content) {
  t_list *new_node;
  t_list *last;

  new_node = malloc(sizeof(t_list));
  if (!new_node)
    return (0);
  new_node->content = content;
  new_node->next = NULL;
  if (*list == NULL) {
    *list = new_node;
    return (1);
  } else {
    last = lst_last(*list);
    last->next = new_node;
    return (1);
  }
}

int has_new_line(
    t_list *list) // node'u alacak içinde \n var mı diye bakacak. bunu read ile
                  // okuma yaptığımız döngüde çağırıcaz
{}

// t_list* create_node(char *str)
// {
// 	t_list* newNode = (t_list*)malloc(sizeof(t_list));
// 	if (!newNode)
// 		exit(1);
// 	newNode->content = str;
// 	newNode->next = NULL;
// 	return newNode;
// }
// #include <stdio.h>
// int main()
// {
// 	t_list* node1 = create_node("A");
// 	t_list* node2 = create_node("B");
// 	t_list* node3 = create_node("C");

// 	node1->next = node2;
// 	node2->next = node3;

// 	t_list* returnNode = lst_last(node1);
// 	printf("Last Node: %s \n", returnNode->content);
// }