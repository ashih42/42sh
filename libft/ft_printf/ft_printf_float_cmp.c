/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_cmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			strip_zero(long double n, int max, long double base)
{
	int	result;
	int	tmp;

	result = ft_nbrlen_base((long long)n, (long long)base);
	while (((n - (long long)n) * base) != 0.0 && result < max)
	{
		n = (n - (long long)n) * base;
		tmp = 0;
		while (result + tmp < max && (long long)n == 0)
		{
			tmp++;
			n = (n - (long long)n) * base;
		}
		if ((long long)n == 0 || result + tmp >= max)
			return (result);
		else
			result += tmp;
		result++;
	}
	return ((result < max) ? result : max);
}

static int	pad_float_cmp(t_printf_flags *flags, long double n, t_bool e, int s)
{
	int	bw;

	bw = strip_zero(n, flags->precision, 10.0);
	if (bw > (int)ft_nbrlen_base((long long)n, 10))
		flags->precision = bw++;
	else
		bw = ft_nbrlen_base((long long)n, 10);
	if (flags->plus || flags->space || flags->negative)
		bw++;
	bw += (e) ? 4 : 0;
	while ((s /= 10) > 9)
		bw++;
	flags->zero_padding = (!flags->left_justify && flags->zero_padding);
	if ((flags->negative || flags->plus) &&
			flags->zero_padding && flags->signed_state != 2)
		write(1, (flags->negative) ? "-" : "+", 1);
	else if (flags->space && flags->zero_padding && flags->signed_state != 2)
		write(1, " ", 1);
	while (bw < flags->width)
	{
		if (!flags->left_justify && flags->signed_state != 2)
			write(1, (flags->zero_padding) ? "0" : " ", 1);
		bw++;
	}
	return (bw);
}

static void	write_float_unsigned_cmp(t_printf_flags *flags, long double n,
		t_bool e, int s)
{
	int	precision;

	if (flags->negative && !flags->zero_padding)
		write(1, "-", 1);
	else if (flags->plus && !flags->zero_padding)
		write(1, "+", 1);
	else if (flags->space && !flags->zero_padding)
		write(1, " ", 1);
	ft_putnbr_base((long long)n, 10, 0);
	if ((precision = flags->precision - ft_nbrlen_base((long long)n, 10)) > 0)
	{
		write(1, ".", ((n - (long long)n) * 10.0) != 0.0 ? 1 : 0);
		while (precision-- && ((n - (long long)n) * 10.0) != 0.0)
		{
			n = (n - (long long)n) * 10.0;
			ft_putnbr_base((unsigned long long)n, 10, 0);
		}
	}
	if (!e)
		return ;
	write(1, (s <= 0) ? "e+" : "e-", (e == 1) ? 2 : 0);
	write(1, (s <= 0) ? "E+" : "E-", (e == 1) ? 0 : 2);
	s = (s < 0) ? -s : s;
	write(1, "0", (s < 10));
	ft_putnbr_base(s, 10, 0);
}

static int	cmp_write_float(t_printf_flags *flags, long double n,
		t_bool e, int s)
{
	int	bw;

	flags->signed_state = 1;
	bw = pad_float_cmp(flags, n, e, (s < 0) ? -s : s);
	if (!flags->left_justify)
		flags->signed_state = 2;
	write_float_unsigned_cmp(flags, n, e, s);
	if (!(flags->left_justify = !flags->left_justify))
		pad_float_cmp(flags, n, e, (s < 0) ? -s : s);
	return (bw);
}

int			write_float_cmp(t_printf_flags *flags, long double n, t_bool e)
{
	long double	t;
	int			s;

	if (!flags->use_precision)
	{
		flags->use_precision = 1;
		flags->precision = 6;
	}
	if ((flags->negative = n < 0.0))
		n = -n;
	t = n;
	s = 0;
	while (e && t != 0.0 && (t >= 10.0 || t < 1.0))
	{
		s += (t < 1.0) ? 1 : -1;
		t *= (t < 1.0) ? 10.0 : 0.1;
	}
	n = round_float(n, flags->precision - ft_nbrlen_base((long long)n, 10));
	t = round_float(t, flags->precision - 1);
	flags->signed_state = 2;
	if (pad_float_cmp(flags, t, e, s) < pad_float_cmp(flags, n, 0, 0) ||
			(int)ft_nbrlen_base((long long)n, 10) > flags->precision)
		return (cmp_write_float(flags, t, e, s));
	else
		return (cmp_write_float(flags, n, 0, 0));
}
