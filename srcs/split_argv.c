#include "ft_42sh.h"

static int	is_ws(char c, char *ws)
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

static void	add_terms_helper(char *ws, t_add_terms *at)
{
	while (at->work_buf[++(at->i)])
	{
		if ((!at->quote && (at->work_buf[at->i] == '\"' ||
			at->work_buf[at->i] == '\'')))
			at->quote = at->work_buf[at->i];
		else if (at->work_buf[at->i] == at->quote)
			at->quote = 0;
		else if (at->work_buf[at->i] == '\\' && (!at->quote ||
			at->work_buf[at->i + 1] == '\'' || at->work_buf[at->i + 1] == '\"'
			|| at->work_buf[at->i + 1] == '$'))
		{
			if (!at->work_buf[++(at->i)])
				break ;
		}
		else if (!at->quote && is_ws(at->work_buf[at->i], ws))
			break ;
	}
}

static void	add_terms(char const *s, t_list **list, char *ws)
{
	t_add_terms	at;

	ft_bzero(&at, sizeof(t_add_terms));
	at.work_buf = ft_strdup(s);
	while (at.work_buf[at.i])
	{
		while (is_ws(at.work_buf[at.i], ws))
			at.i++;
		at.head = at.i--;
		add_terms_helper(ws, &at);
		if (at.i <= at.head)
			continue ;
		at.word = ft_strnew(at.i - at.head);
		ft_strncpy(at.word, at.work_buf + at.head, at.i - at.head);
		ft_lst_add_last(list, ft_lst_new_ref(at.word, sizeof(char *)));
	}
	free(at.work_buf);
}

char		**split_argv(char const *s, char *ws)
{
	char	**result;
	t_list	*list;
	size_t	size;
	char	*path;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	list = NULL;
	add_terms(s, &list, ws);
	if (list == NULL)
		return (NULL);
	size = ft_lst_size(list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);

	path = getcwd(NULL, 0);
	list = get_dir_contents_search(path, size, result);
	free(path);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);

	strip_argv(result);
//	print_char2d(result);
	return (result);
}
