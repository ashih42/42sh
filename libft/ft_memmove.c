/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:46:14 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 16:39:34 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t i;

	if (dst < src)
		ft_memcpy(dst, src, size);
	else if (dst > src)
	{
		i = size;
		while (i--)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}
