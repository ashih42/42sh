#include "ft_42sh.h"

static int	match_file(char *filename, t_list *matchlist)
{
	t_list	*temp;
	t_list	*prev;
	t_list	*next;
	size_t	i;

	i = ft_strlen(filename);
	while (i--)
		if (filename[i] == '/' && (i == 0 || filename[i - 1] != '\\'))
			break ;
	i++;
	temp = matchlist;
	prev = NULL;
	while (temp)
	{
		next = temp->next;
		if (match(filename + i, (char *)temp->content))
			return (1);
		else
			prev = temp;
		temp = next;
	}
	return (0);
}

static void	match_files(t_list **files, t_list *matchlist, int dirs)
{
	t_list	*temp;
	t_list	*prev;
	t_list	*next;

	temp = *files;
	prev = NULL;
	while (temp)
	{
		next = temp->next;
		if ((dirs && !is_dir((char *)temp->content)) ||
			!match_file((char *)temp->content, matchlist))
		{
			if (prev)
				prev->next = temp->next;
			else
				*files = temp->next;
			free(temp->content);
			ft_memdel((void **)&temp);
		}
		else
			prev = temp;
		temp = next;
	}
}

static void	prepend_dirs(char *prepend, t_list *files)
{
	t_list	*temp;
	void	*orig;

	temp = files;
	while (temp)
	{
		orig = temp->content;
		temp->content = build_filepath(prepend, (char *)temp->content);
		if (temp->content)
			free(orig);
		else
			temp->content = orig;
		temp = temp->next;
	}
}

static void	update_files(t_list **files, t_list *matchlist)
{
	t_list	*temp;
	t_list	*result;
	t_list	*tmp;

	temp = *files;
	result = NULL;
	while (temp)
	{
		if ((tmp = get_dir_contents((char *)temp->content, 0)))
		{
			if (ft_lst_search(matchlist, ".", 2, ft_strcmp))
				ft_lstadd(&tmp, ft_lstnew(".", 2));
			if (ft_lst_search(matchlist, "..", 3, ft_strcmp))
				ft_lstadd(&tmp, ft_lstnew("..", 3));
			if (ft_strcmp((char *)temp->content, "/") == 0)
				prepend_dirs("", tmp);
			else if (ft_strcmp((char *)temp->content, ".") != 0)
				prepend_dirs((char *)temp->content, tmp);
			ft_lst_add_last(&result, tmp);
		}
		temp = temp->next;
	}
	ft_lstdel(files, (void (*)(void *, size_t))free);
	*files = result;
}

t_list		*ft_glob(char *s2)
{
	char	**dirs;
	t_list	*files;
	t_list	*matchlist;
	size_t	i;

	if (!should_glob(s2) || valid_brackets(s2) < 0 || !(dirs = split_dirs(s2)))
		return (NULL);
	if (*s2 != '/')
		files = ft_lstnew(".", 2);
	else
		files = ft_lstnew("/", 2);
	i = -1;
	while (files && dirs[++i])
	{
		matchlist = ft_super_factory(dirs[i]);
		update_files(&files, matchlist);
		if (files)
			match_files(&files, matchlist, (dirs[i + 1]) ? 1 : 0);
		ft_lstdel(&matchlist, (void (*)(void *, size_t))free);
	}
	ft_char_array_del(dirs);
	return (expand_filenames(files));
}
