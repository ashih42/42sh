#include "ft_42sh.h"
#include <dirent.h>

t_list	*get_path_executables(t_env *e)
{
	t_list	*path_execs;
	char	**path_dirs;

	path_execs = NULL;
	path_dirs = ft_strsplit(get_variable(e, "PATH"), ':');
	while (*path_dirs)
		ft_printf("|%s|\n", *path_dirs++);
	return (path_execs);
}

t_list	*get_dir_contents(t_env *e)
{
	t_list	*dir_contents;
	// DIR *d;
	// struct dirent *dir;

	(void)e;
	dir_contents = NULL;
	// d = opendir(get_variable(e, "PWD"));
	// if (d)
	// {
	// 	while ((dir = readdir(d)))
	// 		ft_printf("%s\n", dir->d_name);
	// 	closedir(d);
	// }
	// return (1);
	return (dir_contents);
}

int		tab_autocomplete(t_env *e)
{
	get_path_executables(e);
	return (1);
}
