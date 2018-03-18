/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_factory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 06:07:03 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:21:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		find_closing(char *s, int *open)
{
	int	level;
	int	i;
	int	dummy;

	level = 0;
	i = 0;
	if (!open)
		open = &dummy;
	*open = -1;
	while (s[i])
	{
		if (s[i] == '{' && (i == 0 || s[i - 1] != '\\'))
		{
			if (*open < 0)
				*open = i;
			level++;
		}
		else if (s[i] == '}' && (i == 0 || s[i - 1] != '\\'))
			level--;
		if (*open >= 0 && level == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		ft_strtrisect(char *s, char **head, char **tail, char **mid)
{
	int	close;
	int	open;

	close = find_closing(s, &open);
	*head = ft_substr(s, 0, open);
	*tail = ft_substr(s + close + 1, 0, ft_strlen(s + close + 1));
	*mid = ft_substr(s + open + 1, 0, close - open - 1);
}

static t_list	*split_commas(char *s)
{
	t_list	*list;
	char	*head;
	int		brackets;
	char	*str;

	brackets = 0;
	list = 0;
	head = s;
	while (*s)
	{
		(*s == '{' && (s == head || *(s - 1) != '\\')) ? brackets++ : 0;
		(*s == '}' && (s == head || *(s - 1) != '\\')) ? brackets-- : 0;
		if (*s == ',' && brackets == 0 && (s == head || *(s - 1) != '\\'))
		{
			str = ft_strnew(s - head);
			ft_strncpy(str, head, s - head);
			ft_lst_add_last(&list, ft_lst_new_ref(str, sizeof(char *)));
			head = s + 1;
		}
		s++;
	}
	str = ft_strnew(s - head);
	ft_strncpy(str, head, s - head);
	ft_lst_add_last(&list, ft_lst_new_ref(str, sizeof(char *)));
	return (list);
}

static void		ft_str_factory(char *s, t_list **list)
{
	t_strf	f;

	ft_strtrisect(s, &(f.head), &(f.tail), &(f.mid));
	f.mid_list = split_commas(f.mid);
	f.mid_list_head = f.mid_list;
	while (f.mid_list)
	{
		f.temp = ft_strjoin(f.head, f.mid_list->content);
		f.del = f.temp;
		f.temp = ft_strjoin(f.temp, f.tail);
		ft_lst_add_last(list, ft_lst_new_ref(f.temp, sizeof(char *)));
		ft_strdel(&(f.del));
		f.mid_list = f.mid_list->next;
	}
	ft_strdel(&(f.head));
	ft_strdel(&(f.mid));
	ft_strdel(&(f.tail));
	ft_lstdel(&(f.mid_list_head), (void (*)(void *, size_t))free);
}

t_list			*ft_super_factory(char *s)
{
	t_sprf	f;

	ft_bzero(&f, sizeof(t_sprf));
	ft_lst_add_last(&(f.list), ft_lstnew(s, ft_strlen(s) + 1));
	f.head = f.list;
	while (f.list)
	{
		f.str = f.list->content;
		f.next = f.list->next;
		if (find_closing(f.str, NULL) >= 0)
		{
			ft_str_factory(f.str, &(f.list));
			ft_strdel(&(f.str));
			f.next = f.list->next;
			if (f.prev)
				f.prev->next = f.next;
			else
				f.head = f.next;
			free(f.list);
		}
		else
			f.prev = f.list;
		f.list = f.next;
	}
	return (f.head);
}
