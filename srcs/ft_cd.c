#include "ft_42sh.h"

// NOTE: our cd works correctly, but after cd'ing to a symbolic-linked directory, it shows the original directory name, not the symbolic link name
// e.g. cd /; cd tmp;
// now our shell shows we are in /cd/private/tmp because /tmp is a symbolic link for /private/tmp



static int	change_directory(t_env *e, char *directory)
{
	char	*pwd;

	if (!directory || chdir(directory))
		ft_printf("cd: no such file or directory: %s\n", directory);
	else
	{
		set_variable(e, "OLDPWD", get_variable(e, "PWD"));
		pwd = getcwd(NULL, 0);
		set_variable(e, "PWD", pwd);
		free(pwd);
		return (0);
	}
	return (1);
}

int			ft_cd(t_env *e, int argc, char **argv)
{
	char		*homedir;
	char		*oldpwd;
	char		*path;
	int			result;

	homedir = get_variable(e, "HOME");
	oldpwd = get_variable(e, "OLDPWD");
	if (argc > 1)
	{
		if (ft_strequ(argv[1], "-"))
			return (change_directory(e, oldpwd));
		if (argv[1][0] == '~' && homedir &&
			(path = ft_strjoin(homedir, &argv[1][1])))
		{
			result = change_directory(e, path);
			free(path);
			return (result);
		}
		return (change_directory(e, argv[1]));
	}
	return (change_directory(e, homedir));
}
