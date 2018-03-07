/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 02:47:21 by apuel             #+#    #+#             */
/*   Updated: 2018/03/07 02:49:15 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	change_directory(t_env *e, char *directory)
{
	if (!chdir(directory))
	{
		set_variable(e, "OLDPWD", get_variable(e, "PWD"));
		set_variable(e, "PWD", getcwd(NULL, 0));
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
