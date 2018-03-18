/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 06:06:01 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 06:06:20 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_dl_lstdel(t_dl_list **alst, void (*del)(void *, size_t))
{
	t_dl_list	*node;
	t_dl_list	*temp;

	if (alst == NULL || *alst == NULL)
		return ;
	node = *alst;
	*alst = NULL;
	while (node != NULL)
	{
		if (node->content != NULL && del != NULL)
			del(node->content, node->content_size);
		temp = node;
		node = node->next;
		free(temp);
	}
}
