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

/*
**	build_auto_lst()
**
**	Builds a new linked list that references the nodes in either e->tab_execs
**	(mode = 0) or e->tab_dir (mode = 1) that can autocomplete the content of
**	e->buffer.
*/

t_list	*build_auto_lst(t_env *e, int mode, char *cword, size_t *auto_lst_size)
{
	t_list	*new_auto_lst;
	t_list	*curr;

	new_auto_lst = NULL;
	if (!(*e->buffer))
		return (NULL);
	curr = (mode) ? e->tab_dir : e->tab_execs;
	while (curr)
	{
		if (mode || !ft_strncmp(cword, curr->content, ft_strlen(cword)))
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

void	init_tab_auto(t_env *e)
{
	if (e->tab_execs)
		ft_lstdel(&e->tab_execs, (void (*)(void *, size_t))free);
	e->tab_execs = get_path_executables(e);
}

// ft_printf("\x1b[F");

/*
**	get_curr_word()
**
**	This function will get the first non-space character sequence that occurs
**	before the current terminal cursor position.
**
**	Spaces are defined as: ' ', '\t', '\n', '\r', '\f', or '\v'
*/

char	*get_curr_word(t_env *e)
{
	char	*curr_word;
	size_t	wend_pos;
	size_t	tmp_curs;
	size_t	word_len;

	curr_word = NULL;
	tmp_curs = e->cursor;
	while (tmp_curs > 0 && ft_is_space(e->buffer[tmp_curs - 1]))
		tmp_curs--;
	wend_pos = tmp_curs;
	while (tmp_curs > 0 && !ft_is_space(e->buffer[tmp_curs - 1]))
		tmp_curs--;
	word_len = wend_pos - tmp_curs;
	if (word_len && (curr_word = (char *)malloc((word_len + 1) * sizeof(char))))
		ft_strncpy(curr_word, e->buffer + tmp_curs, word_len);
	return (curr_word);
}

/*
**	TODO:
**
**	1. autocomplete a program with a specified path, e.g. ./a TAB TAB TAB
**
**  2. autocomplete on args, grab everything in current directory and
**  add suffix character for folder, symlink, executable, etc.
**
*/

int		tab_autocomplete(t_env *e)
{
	static t_list	*curr_auto_lst = NULL;
	static size_t	auto_lst_size;
	char			*cword;

	if (!(e->tab_pos))
		init_tab_auto(e);
	if (e->reset_tab_auto && curr_auto_lst)
	{
		ft_lstdel(&curr_auto_lst, 0);
		curr_auto_lst = NULL;
	}
	if (!curr_auto_lst)
	{
		cword = get_curr_word(e);
		if (ft_strchr(cword, '/'))
		{
			if (e->tab_dir)
				ft_lstdel(&e->tab_dir, (void (*)(void *, size_t))free);
			e->tab_dir = get_dir_contents(cword, 0);
			e->tab_mode = 1;
			//ft_printf("\n|%s|\n", dir_to_lookup);
		}
		auto_lst_size = 0;
		curr_auto_lst = build_auto_lst(e, e->tab_mode, cword, &auto_lst_size);
		//print_list20(curr_auto_lst);
		e->tab_pos = curr_auto_lst;
		free(cword);
	}
	if (e->tab_pos)
	{
		clear_and_update_term(e, e->tab_pos->content);
		e->tab_pos = (e->tab_pos->next) ? e->tab_pos->next : curr_auto_lst;
		e->reset_tab_auto = 0;
	}
	return (1);
}
