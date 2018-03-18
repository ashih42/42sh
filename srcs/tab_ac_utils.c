#include "ft_42sh.h"

static int		should_remove(char *filename, char *str)
{
	return (!ft_strnequ(filename, str, ft_strlen(str)));
}

static void		build_execs_list(t_env *e, char *word, char *path)
{
	ft_lstdel(&(e->files_head), (void (*)(void *, size_t))free);
	if (path && (path = truncate_backslashes(path)))
	{
		e->files = get_dir_contents(path, 1);
		if (e->files)
			ft_lstrev(&e->files);
		ft_strdel(&path);
	}
	else
		e->files = get_path_executables(e);
	if ((word = truncate_backslashes(word)))
		ft_lst_cond_remove(&(e->files), should_remove, word,
			(void (*)(void *, size_t))free);
	ft_strdel(&word);
	expand_filenames(e->files);
	e->files_head = e->files;
	e->need_files_list = 0;
}

static void		build_files_list(t_env *e, char *word, char *path)
{
	ft_lstdel(&(e->files_head), (void (*)(void *, size_t))free);
	(path) ? path = truncate_backslashes(path) : 0;
	e->files = get_dir_contents((path) ? path : ".", 0);
	ft_strdel(&path);
	if ((word = truncate_backslashes(word)))
		ft_lst_cond_remove(&(e->files), should_remove, word,
			(void (*)(void *, size_t))free);
	ft_strdel(&word);
	ft_lst_sort(&(e->files), ft_strcmp);
	expand_filenames(e->files);
	e->files_head = e->files;
	e->need_files_list = 0;
}

int				ac_first_word(t_env *e, char *word, char *path)
{
	char	*replace;

	if (e->need_files_list)
		build_execs_list(e, word, path);
	if (ft_lst_size(e->files) == 0)
		return (0);
	replace = e->files->content;
	e->files = e->files->next;
	if (e->files == 0)
		e->files = e->files_head;
	ac_replace(e, word, replace);
	return (1);
}

int				ac_not_first_word(t_env *e, char *word, char *path)
{
	char	*replace;

	if (e->need_files_list)
		build_files_list(e, word, path);
	if (ft_lst_size(e->files) == 0)
		return (0);
	replace = e->files->content;
	e->files = e->files->next;
	if (e->files == 0)
		e->files = e->files_head;
	ac_replace(e, word, replace);
	return (1);
}
