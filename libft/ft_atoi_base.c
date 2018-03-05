/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 20:59:19 by apuel             #+#    #+#             */
/*   Updated: 2018/01/31 20:59:20 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_digit_check(char digit, int base)
{
	char	*base_set_lower;
	char	*base_set_upper;
	char	*result;
	long	n;

	base_set_lower = "0123456789abcdefghijklmnopqrstuvwxyz";
	base_set_upper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (digit && (result = ft_strchr(base_set_lower, digit)))
	{
		n = result - base_set_lower;
		if (n < base)
			return ((int)n);
	}
	else if (digit && (result = ft_strchr(base_set_upper, digit)))
	{
		n = result - base_set_upper;
		if (n < base)
			return ((int)n);
	}
	return (-1);
}

int			ft_atoi_base(const char *str, int base)
{
	long long	result;
	long long	n;
	int			digit;

	result = 0;
	n = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		n = -n;
	if (*str == '-' || *str == '+')
		str++;
	while ((digit = ft_digit_check(*str++, base)) != -1)
		result = (result * base) + digit;
	return ((int)(result * n));
}
