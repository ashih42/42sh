/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
**	Conversion formula:
**	https://stackoverflow.com/questions/42012563/
**		convert-unicode-code-points-to-utf-8-and-utf-32
*/

void	ft_putwchar(wchar_t c)
{
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar(0xC0 | (c >> 6));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar(0xE0 | (c >> 12));
		ft_putchar(0x80 | ((c & 0x3F) >> 6));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar(0xF0 | (c >> 18));
		ft_putchar(0x80 | ((c & 0x3F) >> 12));
		ft_putchar(0x80 | ((c & 0x3F) >> 6));
		ft_putchar(0x80 | (c & 0x3F));
	}
}
