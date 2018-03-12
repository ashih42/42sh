#include "ft_42sh.h"

static int is_ws(char c, char *ws)
{
	int i;

	i = 0;
	while (ws[i])
	{
		if (ws[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void		add_terms(char const *s, t_list **list, char *ws)
{
	int		head;
	int		i;
	char	*work_buf;
	char	*word;
	char	quote;

	i = 0;
	quote = 0;
	work_buf = ft_strdup(s);
	while (work_buf[i])
	{
		while (is_ws(work_buf[i], ws))
			i++;
		head = i;
		while (work_buf[i])
		{
			if (!quote && (work_buf[i] == '\"' || work_buf[i] == '\''))
			{
				quote = work_buf[i];
				ft_memmove(work_buf + i, work_buf + i + 1, ft_strlen(work_buf + i + 1) + 1);
				if (!work_buf[i])
					break ;
			}
			if (work_buf[i] == quote)
			{
				quote = 0;
				ft_memmove(work_buf + i, work_buf + i + 1, ft_strlen(work_buf + i + 1) + 1);
				if (!work_buf[i])
					break ;
			}
			if (work_buf[i] == '\\')
			{
				ft_memmove(work_buf + i, work_buf + i + 1, ft_strlen(work_buf + i + 1) + 1);
				if (!work_buf[i])
					break ;
			}
			else if (!quote && is_ws(work_buf[i], ws))
				break ;
			i++;
		}
		if (i > head)
		{
			word = ft_strnew(i - head);
			ft_strncpy(word, work_buf + head, i - head);
			ft_lst_add_last(list, ft_lst_new_ref(word, sizeof(char *)));
		}
	}
	free(work_buf);
}

char			**split_argv(char const *s, char *ws)
{
	char	**result;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	t_list *list = 0;
	add_terms(s, &list, ws);
	if (list == NULL)
		return (NULL);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
	return (result);
}
