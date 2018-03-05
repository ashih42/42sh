/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:41:54 by apuel             #+#    #+#             */
/*   Updated: 2017/12/14 22:41:56 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

unsigned char	*ft_readfile(char *path, size_t *size)
{
	unsigned char	*buffer;
	int				fd;

	if (size)
		*size = ft_getfilesize(path);
	if (size && *size)
		buffer = malloc(*size + 1);
	else
		return ((unsigned char *)0);
	if (buffer)
	{
		fd = open(path, O_RDONLY, 0);
		if (fd >= 0)
		{
			if (read(fd, buffer, *size) < 0)
				ft_memdel((void **)&buffer);
			else
				buffer[*size] = '\0';
			close(fd);
		}
	}
	return (buffer);
}
