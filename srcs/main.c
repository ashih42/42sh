/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 13:47:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	main()
**
**	Our shell loop which consists of:
**
**	1) Listening for user input on stdin
**	2) Parsing the input
**	3) Calling the relevant commands specified in the parsed input
*/

int		main(int argc, char **argv, char **envp)
{
	t_env	e;

	g_e = &e;
	signal(SIGINT, ft_ctrl_c);
	ft_bzero(&e, sizeof(t_env));
	sh_init(&e, envp);
	while (1)
	{
		sh_listen(&e);
		if (!e.buffer)
			break ;
		argv = sh_parse(&e, &argc);
		if (argv)
			sh_dispatcher(&e, argc, argv);
		// NOTE: reusing the argv from main()... what if sh_parse() returns a much longer char **,
		// longer than the amount of memory allocated for the original main()'s argv?

		// To be safe, we should add argc and argv as elements inside t_env e;
	}
	return (0);
}
