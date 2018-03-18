/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:24:24 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:21:51 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			is_valid(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
			return (0);
	}
	return (1);
}

int			ft_setenv(t_env *e, int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("usage: %s var value\n", argv[0]);
		return (1);
	}
	if (ft_isdigit(argv[1][0]) || !is_valid(argv[1]))
	{
		ft_printf("setenv: not an identifier: %s\n", argv[1]);
		return (1);
	}
	set_variable(e, argv[1], argv[2]);
	return (0);
}
