/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 19:25:30 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 19:48:10 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*element;
	t_list	*prev;

	new = (t_list *)0;
	prev = (t_list *)0;
	while (lst)
	{
		element = f(lst);
		if (element)
		{
			if (prev)
				prev->next = element;
			else
				new = element;
			prev = element;
			lst = lst->next;
		}
		else
		{
			ft_lstdel(&new, (void (*)(void *, size_t))free);
			break ;
		}
	}
	return (new);
}
