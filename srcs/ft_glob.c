#include "ft_42sh.h"

static int	match_file(char *filename, t_list *matchlist)
{
	t_list	*temp;
	t_list	*prev;
	t_list	*next;

	temp = matchlist;
	prev = NULL;
	while (temp)
	{
		next = temp->next;
		if (match(filename, (char *)temp->content))
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
		temp->content = ft_strjoin(prepend, (char *)temp->content);
		if (temp->content)
			free(orig);
		else
			temp->content = orig;
		temp = temp->next;
	}
}

static void	update_files(t_list **files)
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

	if (!should_glob(s2) || valid_brackets(s2) < 0 ||
		!(dirs = split_dirs(s2)))
		return (NULL);
	if (*s2 != '/')
		files = get_dir_contents(".", 0);
	else
	{
		files = get_dir_contents("/", 0);
		prepend_dirs("/", files);
	}
	i = -1;
	while (files && dirs[++i])
	{
		if (i > 0)
			update_files(&files);
		matchlist = ft_super_factory(dirs[i]);
		if (files)
			match_files(&files, matchlist, (dirs[i + 1]) ? 1 : 0);
		ft_lstdel(&matchlist, (void (*)(void *, size_t))free);
	}
	return (files);
}
