/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:00:33 by apuel             #+#    #+#             */
/*   Updated: 2017/12/01 12:15:03 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char *)ptr)[i] == (unsigned char)value)
			return ((void *)(((unsigned char *)ptr) + i));
		i++;
	}
	return ((void *)0);
}
