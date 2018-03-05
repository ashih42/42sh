/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 09:23:31 by apuel             #+#    #+#             */
/*   Updated: 2018/01/17 09:23:35 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static unsigned long long	g_next = 1;

/*
**	ft_srand64() exists entirely for compatibility with systems that don't have
**	/dev/urandom, or don't have /dev/urandom available to the caller.
**	Because of this, ft_srand64() should still be called once to ensure
**	compatibility between systems.
*/

void						ft_srand64(unsigned long long seed)
{
	g_next = seed;
}

long long					ft_rand64(void)
{
	static int	fd;
	long long	result;

	if (fd == 0)
		fd = open("/dev/urandom", O_RDONLY, 0);
	if (fd < 0)
		return ((long long)(g_next = g_next * 1103515245 + 12345));
	read(fd, &result, sizeof(long long));
	return (result);
}
