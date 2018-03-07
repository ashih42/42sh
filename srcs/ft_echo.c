/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 03:50:36 by ashih             #+#    #+#             */
/*   Updated: 2018/03/07 14:13:28 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// flags: -n (removes \n at end)

// RIGHT NOW THIS DOESN'T WORK IN GENERAL IF ARGS
// have any quotes,
// have an opening quote only -> need shell to ask for more args


int		print_term(t_env *e, char *str)
{
	char	*value;

	if (str[0] == '$')
	{
		value = get_variable(e, str + 1);
		if (value)
		
			ft_printf(value);
		else
			return (0);
	}
	else
		ft_printf(str);
	return (1);
}

void		ft_echo(t_env *e, int argc, char **argv)
{
	int i;
	int newline;
	int need_space;

	i = (argc >= 1 && ft_strequ(argv[1], "-n")) ? 1 : 0;
	newline = (argc >= 1 && ft_strequ(argv[1], "-n")) ? 0 : 1;
	need_space = 0;
	
	if (argc >= 1 && ft_strequ(argv[1], "-n"))
	{
		newline = 0;
		i = 1;
	}
	while (++i < argc)
	{
		if (need_space)
			ft_printf(" ");
		if (print_term(e, argv[i]))
			need_space = 1;
	}
	ft_printf((newline) ? "\n" : "");
}

