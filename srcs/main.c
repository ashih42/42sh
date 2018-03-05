/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/05 15:46:24 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "ft_42sh.h"

/*
**	initialize_ftsh()
**
**	
*/

// void	initialize_sh()
// {

// }

void	ftsh_loop()
{
	while (1)
	{

	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	while (*envp)
		ft_printf("%s\n", *envp++);
	ftsh_loop();
	return (0);
}
