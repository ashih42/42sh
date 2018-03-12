/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:15:45 by nmei              #+#    #+#             */
/*   Updated: 2018/03/12 14:20:20 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	link_swap(t_list *curr)
{
	t_list	*new_curr_link;
	t_list	*new_next_link;

	new_next_link = curr;
	new_curr_link = (curr->next)->next;
	(curr->next)->next = new_next_link;
	curr->next = new_curr_link;
}

void		ft_list_sort(t_list **lst_start, int (*cmp)())
{
	t_list	*curr_elem;
	t_list	*prev_elem;

	curr_elem = *lst_start;
	if (curr_elem)
	{
		while (curr_elem->next != NULL)
		{
			if (cmp(curr_elem->content, (curr_elem->next)->content) > 0)
			{
				if (curr_elem != *lst_start)
					prev_elem->next = curr_elem->next;
				else
					*lst_start = curr_elem->next;
				link_swap(curr_elem);
				curr_elem = *lst_start;
			}
			else
			{
				prev_elem = curr_elem;
				curr_elem = (curr_elem->next ? curr_elem->next : curr_elem);
			}
		}
	}
}
