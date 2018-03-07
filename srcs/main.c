/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 16:09:22 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "ft_42sh.h"

/*
**	sh_loop()
**
**	Our shell loop which consists of:
**
**	1) Listening for user input on stdin
**	2) Parsing the input
**	3) Calling the relevant commands specified in the parsed input
*/

void	sh_loop()
{
	while (1)
	{
		sh_listen();
		sh_parse();
		sh_dispatcher();
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	env;

	ft_memset(env, 0, sizeof(env));
	(void)argc;
	(void)argv;

	init_sh(&env, envp);
	sh_loop();
	return (0);
}
