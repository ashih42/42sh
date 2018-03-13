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
	e->tab_pos = e->tab_execs;
	// Commenting out directory autocompletion for now... BUT KEEP THIS STUFF!
	// if (e->tab_pwd)
	// 	ft_lstdel(&e->tab_pwd, (void (*)(void *, size_t))free);
	// if ((pwd = getcwd(NULL, 0)))
	// {
	// 	e->tab_pwd = get_dir_contents(pwd, 0);
	// 	free(pwd);
	// }
}

/*
**	TODO:
**	Implement the rest of tab autocompletion.
*/

int		tab_autocomplete(t_env *e)
{
	t_list	*curr;

	if (!(e->tab_pos))
		init_tab_auto(e);
	curr = e->tab_pos;
	while (curr)
	{
		ft_printf("|%s|\n", curr->content);
		curr = curr->next;
	}
	return (1);
}
