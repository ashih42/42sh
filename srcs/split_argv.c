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

static void	add_terms(char const *s, t_list **list, char *ws)
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
		head = i--;
		while (work_buf[++i])
		{
			if ((!quote && (work_buf[i] == '\"' || work_buf[i] == '\'')) &&
				(quote = work_buf[i]) && !work_buf[++i])
				break ;
			if (work_buf[i] == quote && !(quote = 0) && !work_buf[++i])
				break ;
			if (work_buf[i] == '\\' && (!quote || work_buf[i + 1] == quote))
			{
				if (!work_buf[++i])
					break ;
			}
			else if (!quote && is_ws(work_buf[i], ws))
				break ;
		}
		if (i <= head)
			continue ;
		word = ft_strnew(i - head);
		ft_strncpy(word, work_buf + head, i - head);
		ft_lst_add_last(list, ft_lst_new_ref(word, sizeof(char *)));
	}
	free(work_buf);
}

static void	strip_argv(char **argv)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	while (argv[++i])
	{
		quote = 0;
		j = -1;
		while (argv[i][++j])
		{
			if (!quote && (argv[i][j] == '\"' || argv[i][j] == '\''))
			{
				quote = argv[i][j];
				ft_memmove(argv[i] + j, argv[i] + j + 1, ft_strlen(argv[i] + j + 1) + 1);
				if (!argv[i][j])
					break ;
			}
			if (argv[i][j] == quote)
			{
				quote = 0;
				ft_memmove(argv[i] + j, argv[i] + j + 1, ft_strlen(argv[i] + j + 1) + 1);
				if (!argv[i][j])
					break ;
			}
			if (argv[i][j] == '\\' && (!quote || argv[i][j + 1] == quote))
			{
				ft_memmove(argv[i] + j, argv[i] + j + 1, ft_strlen(argv[i] + j + 1) + 1);
				if (!argv[i][j])
					break ;
			}
		}
	}
}

char		**split_argv(char const *s, char *ws)
{
	char	**result;
	t_list	*list;
	size_t	size;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	list = NULL;
	add_terms(s, &list, ws);
	if (list == NULL)
		return (NULL);
	size = ft_lst_size(list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
/*
//	getcwd(NULL, 0);
	list = get_dir_contents_search(path, size, result);
//	free(path);
	result = list_to_array(list);
*/
	strip_argv(result);
	return (result);
}
