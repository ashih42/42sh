#include "ft_42sh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*
**	get_dir_contents()
**
**	Given a dir_path, iterate through the contents of the dir_path and
**	add the names of files, folders, symlinks, etc... into the dir_contents
**	linked list.
**
**	(We only save the actual file/folder/symlink name not the full path.)
**
**	If we are in exec_mode (e_mode = 1) then we only add executable type files
**	(that are NOT directories) to our list.
**
**	Otherwise, we add any kind of file/folder/etc... as long as the name is not
**	'.' or '..'.
*/

t_list	*get_dir_contents(char *dir_path, int e_mode)
{
	t_list			*dir_contents;
	DIR				*d;
	struct dirent	*dir;
	char			*temp_path;

	dir_contents = NULL;
	if ((d = opendir(dir_path)))
	{
		while ((dir = readdir(d)))
		{
			if (e_mode && (temp_path = build_filepath(dir_path, dir->d_name)))
			{
				if (!is_dir(temp_path) && access(temp_path, X_OK) == 0)
					ft_lstadd(&dir_contents,
						ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1));
				free(temp_path);
			}
			else if (!ft_strequ(".", dir->d_name) &&
					!ft_strequ("..", dir->d_name))
				ft_lstadd(&dir_contents,
						ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1));
		}
		closedir(d);
	}
	return (dir_contents);
}

/*
**	get_path_executables()
**
**	Get a linked list with names of all executables found in directories listed
**	in our PATH env variable.
*/

t_list	*get_path_executables(t_env *e)
{
	t_list	*path_execs;
	char	**path_dirs;
	t_list	*dir_cont;
	int		i;

	path_execs = NULL;
	if ((path_dirs = ft_strsplit(get_variable(e, "PATH"), ':')))
	{
		i = 0;
		while (path_dirs[i])
		{
			dir_cont = get_dir_contents(path_dirs[i++], 1);
			ft_lstrev(&dir_cont);
			path_execs = ft_sorted_lst_merge(path_execs, dir_cont, &ft_strcmp);
		}
		ft_char_array_del(path_dirs);
	}
	return (path_execs);
}

void	init_tab_auto(t_env *e)
{
	char	*pwd;

	if (e->tab_execs)
		ft_lstdel(&e->tab_execs, (void (*)(void *, size_t))free);
	e->tab_execs = get_path_executables(e);
	if (e->tab_pwd)
		ft_lstdel(&e->tab_pwd, (void (*)(void *, size_t))free);
	if ((pwd = getcwd(NULL, 0)))
	{
		e->tab_pwd = get_dir_contents(pwd, 0);
		free(pwd);
	}
}

/*
**	build_auto_lst()
**
**	Builds a new linked list that references the nodes in either e->tab_execs
**	(mode = 1) or e->tab_pwd (mode = 0) that can autocomplete the content of
**	e->buffer.
*/

t_list	*build_auto_lst(t_env *e, int mode, size_t *auto_lst_size)
{
	t_list	*new_auto_lst;
	t_list	*curr;
	t_list	*end;

	new_auto_lst = NULL;
	if (!(*e->buffer))
		return (NULL);
	curr = (mode) ? e->tab_execs : e->tab_pwd;
	while (curr)
	{
		if (!ft_strncmp(e->buffer, curr->content, e->buffer_end))
		{
			ft_lstadd(&new_auto_lst,
				ft_lst_new_ref(curr->content, curr->content_size));
			*auto_lst_size = *auto_lst_size + 1;
		}
		curr = curr->next;
	}
	if (new_auto_lst)
		ft_lstrev(&new_auto_lst);
	return (new_auto_lst);
}

void print_list20(t_list *list)
{
	ft_printf("print_list: ");
	while (list)
	{
		ft_printf("%s -> ", list->content);
		list = list->next;
	}
	ft_printf("\n");
}


/*
**	TODO:
**	Implement the rest of tab autocompletion.
**
*/

int		tab_autocomplete(t_env *e)
{
	static t_list	*curr_auto_lst = NULL;
	static size_t	auto_lst_size;
	size_t			n_printed;

	if (!(e->tab_pos))
		init_tab_auto(e);
	if (e->reset_tab_auto && curr_auto_lst)
	{
		ft_lstdel(&curr_auto_lst, 0);
		curr_auto_lst = NULL;
	}
	if (!curr_auto_lst)
	{
		auto_lst_size = 0;
		curr_auto_lst = build_auto_lst(e, 1, &auto_lst_size);
		e->tab_pos = curr_auto_lst;

	}
	if (e->tab_pos)
	{
		clear_and_update_term(e, e->tab_pos->content);
		e->tab_pos = (e->tab_pos->next) ? e->tab_pos->next : curr_auto_lst;
		e->reset_tab_auto = 0;
	}
	return (1);
}
