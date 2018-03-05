/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:16:52 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:12:58 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	dst = (char *)0;
	if (s && f)
		dst = ft_strnew(ft_strlen(s));
	if (dst)
	{
		i = 0;
		while (s[i])
		{
			dst[i] = f(i, s[i]);
			i++;
		}
	}
	return (dst);
}
