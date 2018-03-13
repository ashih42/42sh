/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adv_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:15:45 by nmei              #+#    #+#             */
/*   Updated: 2018/03/12 21:55:22 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_lstrev()
**
**	Given:
**	*begin_list -> A -> B -> C -> D
**
**	Permute so:
**
**	*begin_list -> D -> C -> B -> A 
*/

void	ft_lstrev(t_list **begin_list)
{
	t_list *new_begin;
	t_list *temp_next;

	if (begin_list)
	{
		new_begin = NULL;
		while (*begin_list)
		{
			temp_next = (*begin_list)->next;
			(*begin_list)->next = new_begin;
			new_begin = *begin_list;
			*begin_list = temp_next;
		}
		*begin_list = new_begin;
	}
}

/*
**	ft_sorted_lst_merge
**
**	You have two linked lists in sorted order!
**
**	list1: A -> C -> E
**	list2: B -> D -> F
**
**	This function will give you:
**
**	new: A -> B -> C -> D -> E -> F
*/

t_list	*ft_sorted_lst_merge(t_list *lst1, t_list *lst2, int (*cmp)())
{
	t_list	*new_start;
	t_list	**new_end;

	new_start = NULL;
	new_end = &new_start;
	while (lst1 && lst2)
	{
		if (cmp(lst1->content, lst2->content) < 0)
		{
			*new_end = lst1;
			lst1 = lst1->next;
		}
		else
		{
			*new_end = lst2;
			lst2 = lst2->next;
		}
		new_end = &((*new_end)->next);
	}
	*new_end = (lst1) ? lst1 : lst2;
	return (new_start);
}