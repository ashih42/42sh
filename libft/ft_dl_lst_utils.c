/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:44:19 by nmei              #+#    #+#             */
/*   Updated: 2018/03/09 12:53:43 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dl_list	*ft_dl_lstnew(void const *content, size_t content_size)
{
	t_dl_list	*new;

	if ((new = malloc(sizeof(t_dl_list))))
	{
		if (content_size != 0 && (new->content = malloc(content_size)) == NULL)
		{
			free(new);
			return (NULL);
		}
		if (content)
		{
			ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
		}
		else
		{
			if (new->content != NULL)
				free(new->content);
			new->content = NULL;
			new->content_size = 0;
		}
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void		ft_dl_lst_add_last(t_dl_list **a_dl_lst, t_dl_list *new)
{
	t_dl_list	*curr;

	if (new && a_dl_lst)
	{
		if (*a_dl_lst)
		{
			curr = *a_dl_lst;
			while (curr->next)
				curr = curr->next;
			new->prev = curr;
			curr->next = new;
		}
		else
			*a_dl_lst = new;
	}
}

int			ft_dl_lst_size(t_dl_list *dl_lst)
{
	int	total;

	total = 0;
	while (dl_lst)
	{
		total++;
		dl_lst = dl_lst->next;
	}
	return (total);
}

t_dl_list	*ft_dl_lst_at(t_dl_list *a_dl_lst, unsigned int n)
{
	unsigned int	i;

	if (!a_dl_lst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (a_dl_lst->next == NULL)
			return (NULL);
		a_dl_lst = a_dl_lst->next;
		i++;
	}
	return (a_dl_lst);
}
