/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:32:57 by apuel             #+#    #+#             */
/*   Updated: 2017/12/02 12:39:04 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	itoa_pow(int n, int exp)
{
	long long result;

	result = 1;
	if (exp < 0)
		return (0);
	while (exp--)
		result *= n;
	return (result);
}

char				*ft_itoa(int n)
{
	long long	nb;
	long long	ctr;
	size_t		pos;
	char		*result;

	nb = n;
	pos = 0;
	if (nb < 0)
	{
		pos++;
		nb = -nb;
	}
	ctr = 1;
	while (nb / itoa_pow(10, ctr) != 0)
		ctr++;
	result = ft_strnew(ctr + pos);
	if (result)
	{
		if (pos)
			result[0] = '-';
		while (ctr > 0)
			result[pos++] = ((nb / itoa_pow(10, --ctr)) % 10) + '0';
	}
	return (result);
}
