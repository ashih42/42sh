/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 03:06:21 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:20:48 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static size_t	find_closing_brckt(char *s)
{
	size_t	nbrckts;
	char	brckt;
	size_t	i;

	nbrckts = 1;
	brckt = *s;
	i = 0;
	while (s[++i] && nbrckts)
	{
		if (s[i] == brckt && s[i - 1] != '\\')
			nbrckts++;
		if (((brckt == '{' && s[i] == '}') ||
			(brckt == '[' && s[i] == ']')) &&
			s[i - 1] != '\\')
			nbrckts--;
	}
	return (i - 1);
}

static void		add_terms_helper(t_add_terms *at)
{
	while (at->work_buf[++(at->i)])
	{
		if ((at->work_buf[at->i] == '{' || at->work_buf[at->i] == '['))
			at->i += find_closing_brckt(&(at->work_buf[at->i]));
		else if (at->work_buf[at->i] == '\\')
		{
			if (!at->work_buf[++(at->i)])
				break ;
		}
		else if (at->work_buf[at->i] == '/')
			break ;
	}
}

static void		add_terms(char const *s, t_list **list)
{
	t_add_terms	at;

	ft_bzero(&at, sizeof(t_add_terms));
	at.work_buf = ft_strdup(s);
	while (at.work_buf[at.i])
	{
		while (at.work_buf[at.i] == '/')
			at.i++;
		at.head = at.i--;
		add_terms_helper(&at);
		if (at.i <= at.head)
			continue ;
		at.word = ft_strnew(at.i - at.head);
		ft_strncpy(at.word, at.work_buf + at.head, at.i - at.head);
		ft_lst_add_last(list, ft_lst_new_ref(at.word, sizeof(char *)));
	}
	free(at.work_buf);
}

char			**split_dirs(char const *s)
{
	char	**result;
	t_list	*list;
	size_t	size;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	list = NULL;
	add_terms(s, &list);
	if (list == NULL)
		return (NULL);
	size = ft_lst_size(list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
	return (result);
}
