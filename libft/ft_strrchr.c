/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:06:33 by apuel             #+#    #+#             */
/*   Updated: 2017/11/28 23:20:46 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int value)
{
	size_t len;

	len = ft_strlen(str) + 1;
	while (len--)
		if (str[len] == (char)value)
			return ((char *)&str[len]);
	return ((char *)0);
}
