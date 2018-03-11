#include "ft_42sh.h"
#include <dirent.h>

t_list	*get_dir_contents(char *dir_path, int check_exec_mode)
{
	t_list			*dir_contents;
	DIR				*d;
	struct dirent	*dir;

	(void)check_exec_mode;
	dir_contents = NULL;
	d = opendir(dir_path);
	if (d)
	{
		while ((dir = readdir(d)))
			ft_printf("%s\n", dir->d_name);
		closedir(d);
	}
	return (dir_contents);
}

t_list	*get_path_executables(t_env *e)
{
	t_list	*path_execs;
	char	**path_dirs;
	int		i;

	path_execs = NULL;
	if ((path_dirs = ft_strsplit(get_variable(e, "PATH"), ':')))
	{
		i = 0;
		while (path_dirs[i])
		{
			get_dir_contents(path_dirs[i++], 1);
		}
		ft_char_array_del(path_dirs);
	}
	return (path_execs);
}

int		tab_autocomplete(t_env *e)
{
	get_path_executables(e);
	return (1);
}
