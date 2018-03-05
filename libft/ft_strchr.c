/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:01:58 by apuel             #+#    #+#             */
/*   Updated: 2017/11/15 20:26:15 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int value)
{
	while (*str)
	{
		if (*str == (char)value)
			return ((char *)str);
		str++;
	}
	if (*str == (char)value)
		return ((char *)str);
	return ((char *)0);
}
