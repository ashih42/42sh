/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 03:50:36 by ashih             #+#    #+#             */
/*   Updated: 2018/03/07 04:09:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// flags: -n (removes \n at end)

// RIGHT NOW THIS DOESN'T WORK IN GENERAL IF ARGS
// have any quotes,
// have an opening quote only -> need shell to ask for more args

void		ft_echo(t_env *e, int argc, char **argv)
{
	(void)e;
	
	int i = 0;
	int need_space = 0;
	int newline = 1;

	if (argc >= 1 && ft_strequ(argv[1], "-n"))
	{
		newline = 0;
		i = 1;
	}
	while (++i < argc)
	{
		if (need_space)
			ft_printf(" ");
		ft_printf(argv[i]);
		need_space = 1;
	}
	ft_printf((newline) ? "\n" : "");
}

