/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:58 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 21:16:38 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(to_find);
	if (ft_strlen(str) == 0 && len == 0)
		return ((char *)str);
	while (str[i])
	{
		if (ft_strncmp(&str[i], to_find, len) == 0)
			return ((char *)&str[i]);
		i++;
	}
	return ((char *)0);
}
