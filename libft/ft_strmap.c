/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:03:32 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:12:22 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	size_t	i;

	dst = (char *)0;
	if (s && f)
		dst = ft_strnew(ft_strlen(s));
	if (dst)
	{
		i = 0;
		while (s[i])
		{
			dst[i] = f(s[i]);
			i++;
		}
	}
	return (dst);
}
