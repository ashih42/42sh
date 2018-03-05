/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	round_hex_float(long double f, int position)
{
	long double	tmp;
	long double	test;

	tmp = 8.0 / 16.0;
	test = f;
	while (position-- > 0)
	{
		tmp /= 16.0;
		test = (test - (long long)test) * 16.0;
		if (test == 0.0)
			return (f);
	}
	return (f + tmp);
}

static int			pad_hex_float(t_printf_flags *flags, long double n,
		t_bool u, int s)
{
	int	bw;

	if (flags->use_precision)
		bw = flags->precision;
	else
		bw = strip_zero(n, 10000, 16.0);
	if (bw > (int)ft_nbrlen_base((long long)n, 16))
		bw++;
	bw += (flags->plus || flags->space || flags->negative);
	bw += 4 + ft_nbrlen_base((s < 0) ? -s : s, 10);
	flags->zero_padding = (!flags->left_justify && flags->zero_padding);
	if ((flags->negative || flags->plus) &&
			flags->zero_padding && flags->signed_state != 2)
		write(1, (flags->negative) ? "-" : "+", 1);
	else if (flags->space && flags->zero_padding && flags->signed_state != 2)
		write(1, " ", 1);
	if (flags->zero_padding && flags->signed_state != 2)
		write(1, (u) ? "0X" : "0x", 2);
	while (bw < flags->width)
	{
		if (!flags->left_justify && flags->signed_state != 2)
			write(1, (flags->zero_padding) ? "0" : " ", 1);
		bw++;
	}
	return (bw);
}

static void			write_float_hex_unsigned(t_printf_flags *flags,
		long double n, t_bool u, int s)
{
	int	precision;

	if (flags->negative && !flags->zero_padding)
		write(1, "-", 1);
	else if (flags->plus && !flags->zero_padding)
		write(1, "+", 1);
	else if (flags->space && !flags->zero_padding)
		write(1, " ", 1);
	write(1, (u) ? "0X" : "0x", (flags->zero_padding) ? 0 : 2);
	ft_putnbr_base((long long)n, 16, u);
	if (((n = (n - (long long)n) * 16.0) != 0.0 && !flags->use_precision) ||
			(flags->use_precision && (precision = flags->precision)))
	{
		write(1, ".", 1);
		while ((!flags->use_precision && n != 0.0) ||
			(flags->use_precision && precision--))
		{
			ft_putnbr_base((long long)n, 16, u);
			n = (n - (long long)n) * 16.0;
		}
	}
	write(1, (s <= 0) ? "p+" : "p-", (u) ? 0 : 2);
	write(1, (s <= 0) ? "P+" : "P-", (u) ? 2 : 0);
	s = (s < 0) ? -s : s;
	ft_putnbr_base(s, 10, 0);
}

int					write_float_hex(t_printf_flags *flags, long double n,
		t_bool u)
{
	int			bw;
	int			s;

	if ((flags->negative = n < 0.0))
		n = -n;
	s = 0;
	while (n != 0.0 && (n >= 2.0 || n < 1.0))
	{
		s += (n < 1.0) ? 1 : -1;
		n *= (n < 1.0) ? 2.0 : 0.5;
	}
	if (flags->use_precision)
		n = round_hex_float(n, flags->precision);
	flags->signed_state = 1;
	bw = pad_hex_float(flags, n, u, s);
	if (!flags->left_justify)
		flags->signed_state = 2;
	write_float_hex_unsigned(flags, n, u, s);
	if (!(flags->left_justify = !flags->left_justify))
		pad_hex_float(flags, n, u, s);
	return (bw);
}

int					float_writer_hex(t_printf_flags *flags, va_list *args,
		char *type)
{
	if (ft_strcmp(type, "La") == 0)
		return (write_float_hex(flags, va_arg(*args, long double), 0));
	if (ft_strchr(type, 'a'))
		return (write_float_hex(flags, va_arg(*args, double), 0));
	if (ft_strcmp(type, "LA") == 0)
		return (write_float_hex(flags, va_arg(*args, long double), 1));
	if (ft_strchr(type, 'A'))
		return (write_float_hex(flags, va_arg(*args, double), 1));
	return (-42);
}
