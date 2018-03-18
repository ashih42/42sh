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
	wend_pos = e->cursor;
	while (e->cursor > 0 && !ft_is_space(e->buffer[e->cursor - 1]))
		e->cursor--;
	word_len = wend_pos - e->cursor;
	if (word_len && (curr_word = ft_strnew(word_len + 1)))	
		ft_strncpy(curr_word, e->buffer + e->cursor, word_len);
	return (curr_word);
}


/*
int		tab_autocomplete(t_env *e)
{
	if (cursor is in middle of word)
		move cursor to last pos of world 
	
	autocomplete
}
*/
/*
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
*/


int		should_remove(char *filename, char *str)
{
	return (!ft_strnequ(filename, str, ft_strlen(str)));
}

void	build_execs_list(t_env *e, char *word, char *path)
{
	ft_lstdel(&(e->files), (void (*)(void *, size_t))free);
	
	if (path)
	{
		e->files = get_dir_contents(path, 1);
		if (e->files)
			ft_lstrev(&e->files);
	}
	else
		e->files = get_path_executables(e);
	ft_lst_cond_remove(&(e->files), should_remove, word,
		(void (*)(void *, size_t))free);
	e->files_head = e->files;
	e->need_files_list = 0;
}


void	build_files_list(t_env *e, char *word, char *path)
{
	ft_lstdel(&(e->files), (void (*)(void *, size_t))free);
	
	e->files = get_dir_contents((path) ? path : ".", 0);
	ft_lst_cond_remove(&(e->files), should_remove, word,
		(void (*)(void *, size_t))free);
	ft_lst_sort(&(e->files), ft_strcmp);

	e->files_head = e->files;
	e->need_files_list = 0;
}

void	ac_repos_cursor(t_env *e, size_t old_cursor)
{
	size_t	i;

	move_cursor(e, 0, e->cursor);
	i = 0;
	while (i < old_cursor)
	{
		move_cursor(e, 1, 1);
		i++;	
	}
	while (!ft_is_space(e->buffer[e->cursor]) && e->buffer[e->cursor] != '\0')
		move_cursor(e, 1, 1);
}

void	ac_replace(t_env *e, char *word, char *replace)
{
	size_t	old_cursor;

	while (ft_strlen(e->buffer) - ft_strlen(word) + ft_strlen(replace)
			> e->buffer_size)
		extend_buffer(e);
	ft_memmove(e->buffer + e->cursor + ft_strlen(replace),
		e->buffer + e->cursor + ft_strlen(word),
		ft_strlen(e->buffer + ft_strlen(word)) + 1);
	ft_strncpy(e->buffer + e->cursor, replace, ft_strlen(replace));

	ft_putstr("\r\x1B[K");
	e->promt_len = ft_printf("%s %s > ", SPESHELL, get_variable(e, "PWD"));
	old_cursor = e->cursor;
	ft_printf("%s", e->buffer);
	e->cursor = ft_strlen(e->buffer);
	e->buffer_end = ft_strlen(e->buffer);
	ac_repos_cursor(e, old_cursor);
}

int		ac_first_word(t_env *e, char *word, char *path)
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

int		ac_not_first_word(t_env *e, char *word, char *path)
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

void	get_word_path(t_env *e, char **word, char **path)
{
	int		i;

	*path = 0;
	if (!*word || !ft_strchr(*word, '/'))
		return ;
	*path = *word;
	i = -1;
	while (ft_strchr(*path + ++i, '/'))
		e->cursor++;
	*word = ft_strdup(*path + i);
	(*path)[i] = '\0';
}

int		is_first_word(t_env *e)
{
	size_t	curs;

	curs = e->cursor;
	while (curs > 0 && !ft_is_space(e->buffer[curs - 1]))
		curs--;
	while (curs > 0 && ft_is_space(e->buffer[curs - 1]))
		curs--;
	if (e->buffer[curs] && !ft_is_space(e->buffer[curs]))
		return (1);
	else
		return (0);
}

int		tab_autocomplete(t_env *e)
{
	char	*word;
	char	*path;
	size_t	temp;
	int		result;

	temp = e->cursor;
	word = get_curr_word(e);
	get_word_path(e, &word, &path);
	
	if (is_first_word(e))
		result = ac_first_word(e, word, path);
	else
		result = ac_not_first_word(e, word, path);
	if (!result)
		e->cursor = temp;
	ft_strdel(&word);
	ft_strdel(&path);
	return (1);
}
