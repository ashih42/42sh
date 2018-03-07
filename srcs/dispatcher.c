/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:59 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 02:17:25 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_dispatcher()
**
**	This function should take the cmds/arguments that the parser has identified:
**
**	1) Check if the command is a local one (i.e. builtin)
**	2) If it's not local, check if the cmd is located in PATH env folders
**	3) If the cmd is not located in the specified PATHS check if the the cmd was
**	   provided as a literal path.
*/

void	ft_cd(t_env *e, int argc, char **argv)
{
	char		*homedir;
	char		*pwd;
	char		*oldpwd;

	if (argc > 1)
	{
		pwd = get_variable(e, "PWD");
		homedir = get_variable(e, "HOME");
		oldpwd = get_variable(e, "OLDPWD");
		if (ft_strequ(argv[1], "-"))
		{
			if (!chdir(oldpwd))
				set_variable(e, "OLDPWD", pwd);
		}
		else if (ft_strequ(argv[1], "~/"))
		{
			if (!chdir(homedir))
				set_variable(e, "OLDPWD", pwd);
		}
		else if (!chdir(argv[1]))
			set_variable(e, "OLDPWD", pwd);
		set_variable(e, "PWD", getcwd(NULL, 0));
	}
}

void	sh_dispatcher(t_env *e, int argc, char **argv)
{
	char	**envp;

	if (argc)
	{
		if (ft_strequ(argv[0], "cd"))
			ft_cd(e, argc, argv);
		else
		{
			if ((envp = serialize_envp(e)))
			{
				execve(argv[0], argv, envp);
				free_serialized_envp(envp);
			}
			else
				ft_printf("{robot} [!] Failed to allocate envp!\n");
		}
	}
}
