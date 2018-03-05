/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:56:50 by apuel             #+#    #+#             */
/*   Updated: 2017/12/02 12:22:59 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *element;
	t_list *next;

	if (alst)
	{
		element = *alst;
		while (element)
		{
			next = element->next;
			ft_lstdelone(&element, del);
			element = next;
		}
		*alst = (t_list *)0;
	}
}
