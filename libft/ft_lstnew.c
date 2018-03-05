/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:38:27 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 15:28:19 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*element;
	void	*copy;

	element = malloc(sizeof(t_list));
	if (element)
	{
		copy = (void *)0;
		if (content)
			copy = malloc(content_size);
		else
			content_size = 0;
		if (copy)
			ft_memcpy(copy, content, content_size);
		if (!content || copy)
		{
			element->next = (t_list *)0;
			element->content = copy;
			element->content_size = content_size;
		}
		else
			ft_memdel((void **)&element);
	}
	return (element);
}
