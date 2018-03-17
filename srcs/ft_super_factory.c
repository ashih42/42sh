#include "ft_42sh.h"

static int		find_closing(char *s)
{
	int level;
	int i;

	level = 1;
	i = ft_strchr(s, '{') - s + 1;
	while (s[i])
	{
		if (s[i] == '{')
			level++;
		else if (s[i] == '}')
			level--;
		if (level == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		ft_strtrisect(char *s, char **head, char **tail, char **mid)
{
	int	close;

	close = find_closing(s);
	*head = ft_substr(s, 0, ft_strchr(s, '{') - s);
	*tail = ft_substr(s + close + 1, 0, ft_strlen(s + close + 1));
	*mid = ft_substr(ft_strchr(s, '{') + 1, 0,
		s + close - ft_strchr(s, '{') - 1);
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
		(*s == '{') ? brackets++ : 0;
		(*s == '}') ? brackets-- : 0;
		if (*s == ',' && brackets == 0)
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
	t_strf		f;

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
	t_sprf		f;

	ft_bzero(&f, sizeof(t_sprf));
	ft_lst_add_last(&(f.list), ft_lstnew(s, ft_strlen(s) + 1));
	f.head = f.list;
	while (f.list)
	{
		f.str = f.list->content;
		f.next = f.list->next;
		if (ft_strchr(f.str, '{'))
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
