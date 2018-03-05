/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:29:42 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:15:36 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	i;

	dst = (char *)0;
	if (s)
		dst = ft_strnew(len);
	if (dst)
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			dst[i] = s[start + i];
			i++;
		}
	}
	return (dst);
}
