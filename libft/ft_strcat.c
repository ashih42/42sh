/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:59:41 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 16:42:52 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(dst);
	while (src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (dst);
}
