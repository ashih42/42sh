/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:47:08 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:20:20 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*dst;

	if (!s)
		return ((char *)0);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	len = ft_strlen(s);
	if (len)
		while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
			len--;
	dst = ft_strnew(len);
	if (dst)
		ft_strncpy(dst, s, len);
	return (dst);
}
