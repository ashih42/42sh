/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilesize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:41:35 by apuel             #+#    #+#             */
/*   Updated: 2017/12/14 22:41:40 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

size_t	ft_getfilesize(char *path)
{
	unsigned char	buffer[BUFFER_SIZE];
	size_t			size;
	int				fd;
	int				br;

	fd = open(path, O_RDONLY, 0);
	size = 0;
	if (fd >= 0)
	{
		while ((br = read(fd, buffer, BUFFER_SIZE)) > 0)
			size += br;
		close(fd);
	}
	return (size);
}
