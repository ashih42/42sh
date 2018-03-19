/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:06:44 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 21:43:06 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	change_directory(t_env *e, char *directory)
{
	char	*pwd;

	if (!directory || chdir(directory))
		ft_printf("cd: no such file or directory: %s\n", directory);
	else
	{
		set_variable(e, "OLDPWD", get_variable(e, "PWD"));
		if ((pwd = getcwd(NULL, 0)))
		{
			set_variable(e, "PWD", pwd);
			ft_strdel(&pwd);
		}
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
			ft_strdel(&path);
			return (result);
		}
		return (change_directory(e, argv[1]));
	}
	return (change_directory(e, homedir));
}
