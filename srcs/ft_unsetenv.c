/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 06:00:46 by ashih             #+#    #+#             */
/*   Updated: 2018/03/07 06:21:41 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// should this REMOVE or SET TO EMPTY STRING ??

void		ft_unsetenv(t_env *e, int argc, char **argv)
{
	if (argc >= 2)
	{
		del_variable(e, argv[1]);
//		if (get_variable(e, argv[1]))
//			set_variable(e, argv[1], "");
	}

}

