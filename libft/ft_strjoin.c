/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:39:59 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:16:08 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = (char *)0;
	if (s1 && s2)
		dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (dst)
	{
		ft_strcpy(dst, s1);
		ft_strcat(dst, s2);
	}
	return (dst);
}
