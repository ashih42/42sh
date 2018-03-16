/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cond_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 01:16:42 by ashih             #+#    #+#             */
/*   Updated: 2018/03/12 17:24:45 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_cond_remove(t_list **list, int (*cond)(char *, char*),
	char *key, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*prev;
	t_list	*next;

	temp = *list;
	prev = 0;
	while (temp)
	{
		next = temp->next;
		if (cond((char *)temp->content, key))
		{
			if (prev)
				prev->next = temp->next;
			else
				*list = temp->next;
			if (del)
				del(temp->content, temp->content_size);
			ft_memdel((void **)&temp);
		}
		else
			prev = temp;
		temp = next;
	}
}
