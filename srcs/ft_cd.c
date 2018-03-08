#include "ft_42sh.h"

static void	change_directory(t_env *e, char *directory)
{
	char	*pwd;

	if (chdir(directory))
		ft_printf("cd: no such file or directory: %s\n", directory);
	else
	{
		set_variable(e, "OLDPWD", get_variable(e, "PWD"));
		pwd = getcwd(NULL, 0);
		set_variable(e, "PWD", pwd);
		free(pwd);
	}
}

void		ft_cd(t_env *e, int argc, char **argv)
{
	char		*homedir;
	char		*pwd;
	char		*oldpwd;
	char		*path;

	pwd = get_variable(e, "PWD");
	homedir = get_variable(e, "HOME");
	oldpwd = get_variable(e, "OLDPWD");
	if (argc > 1)
	{
		if (ft_strequ(argv[1], "-"))
			change_directory(e, oldpwd);
		else
		{
			if (argv[1][0] == '~' && (path = ft_strjoin(homedir, &argv[1][1])))
			{
				change_directory(e, path);
				free(path);
			}
			else
				change_directory(e, argv[1]);
		}
	}
	else
		change_directory(e, homedir);
}
