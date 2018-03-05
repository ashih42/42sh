/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:14:43 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:07:42 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(to_find);
	if ((n == 0 || ft_strlen(str) == 0) && len == 0)
		return ((char *)str);
	if (n < len)
		return ((char *)0);
	while (str[i] && i <= n - len)
	{
		if (ft_strncmp(&str[i], to_find, len) == 0)
			return ((char *)&str[i]);
		i++;
	}
	return ((char *)0);
}
