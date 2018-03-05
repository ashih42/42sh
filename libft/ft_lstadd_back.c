/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:24:36 by apuel             #+#    #+#             */
/*   Updated: 2017/12/02 12:37:59 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *element;

	if (alst)
	{
		if (!(*alst))
			*alst = new;
		else
		{
			element = *alst;
			while (element->next)
				element = element->next;
			element->next = new;
		}
	}
}
