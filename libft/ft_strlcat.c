/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:37:20 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 18:43:15 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t len;
	size_t i;

	i = 0;
	len = 0;
	while (len < n && dst[len])
		len++;
	if (n > 0)
	{
		while (src[i] && len + i < n - 1)
		{
			dst[len + i] = src[i];
			i++;
		}
		if (len < n)
			dst[len + i] = '\0';
	}
	return (len + ft_strlen(src));
}
