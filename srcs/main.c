/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 17:15:02 by ashih            ###   ########.fr       */
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

void	sh_loop(t_env *e)
{
	while (1)
	{
		sh_listen(e);
		sh_parse(e);
		sh_dispatcher(e);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	
	(void)argc;
	(void)argv;

	init_sh(&e, envp);
	sh_loop(&e);

//	char temp[BUFFER_SIZE];
	printf("getcwd = %s\n", getcwd(0, 0));
//	printf("temp = %s\n", temp);
	return (0);
}
