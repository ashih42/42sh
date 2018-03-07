/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:59 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 18:08:31 by ashih            ###   ########.fr       */
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

void	ft_cd(t_env *e)
{
	// TODO: how to do case: cd (no arg[1] -> cd $HOME)
	// how to check argc??

	if (ft_strequ(e->args[1], "-"))
	{
		chdir(e->oldpwd);
		SWAP(e->oldpwd, e->pwd, char *);
	}
	else
	{
		e->oldpwd = e->pwd;
		chdir(e->args[1]);
		e->pwd = getcwd(0, 0);
	}

}



void	run(t_env *e)
{
	if (ft_strequ(e->args[0], "cd"))
		ft_cd(e);
	else
		execvp(e->args[0], e->args);
	exit(0);
}





void	sh_dispatcher(t_env *e)
{
//	ft_printf("{robot}dispatching...\n");
	int pid;
	int child_status;
	pid = fork();
	if (pid < 0)
	{
		ft_puterror("fork() failed", 0, 0);
		exit(0);
	}
	if (pid == 0)
		run(e);
	else
		wait(&child_status);
}