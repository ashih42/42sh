/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:35:57 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 16:46:32 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(dst);
	while (src[i] && i < n)
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (dst);
}
