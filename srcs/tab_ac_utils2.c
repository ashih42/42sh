/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_ac_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 05:02:38 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:20:39 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

t_list			*get_dir_contents(char *dir_path, int e_mode)
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

t_list			*get_path_executables(t_env *e)
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

char			*truncate_backslashes(char *s)
{
	char	*cpy;
	size_t	i;

	if ((cpy = ft_strdup(s)))
	{
		i = -1;
		while (cpy[++i])
			if (cpy[i] == '\\')
			{
				ft_memmove(cpy + i, cpy + i + 1, ft_strlen(cpy + i + 1) + 1);
				if (!cpy[i])
					break ;
			}
	}
	return (cpy);
}

static void		ac_repos_cursor(t_env *e, size_t old_cursor)
{
	size_t	i;

	move_cursor(e, 0, e->cursor);
	i = 0;
	while (i < old_cursor)
	{
		move_cursor(e, 1, 1);
		i++;
	}
	while ((!ft_is_space(e->buffer[e->cursor]) ||
		(e->cursor > 0 && e->buffer[e->cursor - 1] == '\\')) &&
		e->buffer[e->cursor] != '\0')
		move_cursor(e, 1, 1);
}

void			ac_replace(t_env *e, char *word, char *replace)
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
