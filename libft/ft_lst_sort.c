/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 03:19:25 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 03:21:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		insert(t_list **head, t_list *new_node, int (*cmp)())
{
	t_list	*current;

	if (*head == NULL || cmp((*head)->content, new_node->content) >= 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL &&
			cmp(current->next->content, new_node->content) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

void			ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*sorted;
	t_list	*current;
	t_list	*next;

	sorted = NULL;
	current = *begin_list;
	while (current != NULL)
	{
		next = current->next;
		insert(&sorted, current, cmp);
		current = next;
	}
	*begin_list = sorted;
}
