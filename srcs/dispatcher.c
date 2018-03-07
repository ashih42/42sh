/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:59 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 04:00:42 by ashih            ###   ########.fr       */
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

static int	built_ins(t_env *e, int argc, char **argv)
{
	if (ft_strequ(argv[0], "cd"))
		ft_cd(e, argc, argv);
	else if (ft_strequ(argv[0], "echo"))
		ft_echo(e, argc, argv);
	else
		return (0);
	return (1);
}

void		sh_dispatcher(t_env *e, int argc, char **argv)
{
	char	**envp;

	if (argc)
	{
		if (!built_ins(e, argc, argv))
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
