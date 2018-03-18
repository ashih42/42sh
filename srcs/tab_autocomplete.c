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



// ft_printf("\x1b[F");

size_t	get_cword_start(t_env *e, size_t cursor_pos)
{
	while (cursor_pos > 0 && ft_is_space(e->buffer[cursor_pos - 1]))
		cursor_pos--;
	while (cursor_pos > 0 && !ft_is_space(e->buffer[cursor_pos - 1]))
		cursor_pos--;
	return (cursor_pos);
}

/*
**	get_curr_word()
**
**	This function will get the first non-space character sequence that occurs
**	before the specified cursor_pos.
**
**	If the cursor_pos is in the middle of a word, then the function will return
**	the entire word.
**
**	Spaces are defined as: ' ', '\t', '\n', '\r', '\f', or '\v'
*/

char	*get_curr_word(t_env *e)
{
	char	*curr_word;
	size_t	wend_pos;
	size_t	word_len;

	curr_word = NULL;
	while (e->buffer[e->cursor] && !ft_is_space(e->buffer[e->cursor]))
		e->cursor++;
	while (e->cursor > 0 && ft_is_space(e->buffer[e->cursor - 1]))
		e->cursor--;
	wend_pos = e->cursor;
	while (e->cursor > 0 && !ft_is_space(e->buffer[e->cursor - 1]))
		e->cursor--;
	word_len = wend_pos - e->cursor;
	if (word_len && (curr_word = ft_strnew(word_len + 1)))	
		ft_strncpy(curr_word, e->buffer + e->cursor, word_len);
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

/*
int		tab_autocomplete(t_env *e)
{
	if (cursor is in middle of word)
		move cursor to last pos of world 
	
	autocomplete
}
*/

void	insert(t_list **head, t_list *new_node, int (*cmp)())
{
	t_list	*current;

	if (*head == NULL || cmp((*head)->content, new_node->content) >= 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL &&
			cmp(current->next->content, new_node->content) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*sorted;
	t_list	*current;
	t_list	*next;

	sorted = NULL;
	current = *begin_list;
	while (current != NULL)
	{
		next = current->next;
		insert(&sorted, current, cmp);
		current = next;
	}
	*begin_list = sorted;
}



int		should_remove(char *filename, char *str)
{
	return (!ft_strnequ(filename, str, ft_strlen(str)));
}


void	ac_first_word(t_env *e, char *word)
{
	ft_printf("ac_first_word()\n");
	(void)e;
	(void)word;
}

void	build_files_list(t_env *e, char *word)
{
	ft_lstdel(&(e->files), (void (*)(void *, size_t))free);
	
	e->files = get_dir_contents(".", 0);
	ft_lst_cond_remove(&(e->files), should_remove, word,
		(void (*)(void *, size_t))free);
	ft_list_sort(&(e->files), ft_strcmp);

	e->files_head = e->files;
	e->need_files_list = 0;
}

void	ac_replace(t_env *e, char *word, char *replace)
{
	while (ft_strlen(e->buffer) - ft_strlen(word) + ft_strlen(replace)
			> e->buffer_size)
		extend_buffer(e);
	ft_memmove(e->buffer + ft_strlen(replace), e->buffer + ft_strlen(word),
		ft_strlen(e->buffer + e->cursor));
	ft_strncpy(e->buffer + e->cursor, replace, ft_strlen(replace));
	// ac_refresh yo
	ft_putstr("\r\x1B[K");
	e->promt_len = ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	ft_printf("%s", e->buffer);
	e->cursor = ft_strlen(e->buffer);
	e->buffer_end = ft_strlen(e->buffer);
}

void	ac_not_first_word(t_env *e, char *word)
{
	char	*replace;

	if (e->need_files_list)
		build_files_list(e, word);
	if (ft_lst_size(e->files) == 0)
		return ;
	replace = e->files->content;
	e->files = e->files->next;
	if (e->files == 0)
		e->files = e->files_head;
	ac_replace(e, word, replace);
//	ft_printf("replace = %s\n", replace);
}

int		tab_autocomplete(t_env *e)
{
	char *word = get_curr_word(e);

	if (e->cursor == 0)
		ac_first_word(e, word);
	else
		ac_not_first_word(e, word);
	ft_strdel(&word);
	return (1);
}


/*
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
		cword = get_curr_word(e, e->cursor);
		if (cword)
		{
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
	}
	if (e->tab_pos)
	{
//		insert_and_update_term(e, e->tab_pos->content, get_cword_start(e, e->cursor));
		clear_and_update_term(e, e->tab_pos->content);
		e->tab_pos = (e->tab_pos->next) ? e->tab_pos->next : curr_auto_lst;
		e->reset_tab_auto = 0;
	}
	return (1);
}
*/