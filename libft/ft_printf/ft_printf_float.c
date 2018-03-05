/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	round_float(long double f, int position)
{
	long double	tmp;
	long double	test;

	tmp = 0.5;
	test = f;
	while (position-- > 0)
	{
		tmp /= 10.0;
		test = (test - (long long)test) * 10.0;
		if (test == 0.0)
			return (f);
	}
	return (f + tmp);
}

static int	pad_float(t_printf_flags *flags, long double n, t_bool e, int s)
{
	int	bw;

	bw = (flags->precision) ? flags->precision + 1 : 0;
	bw += ft_nbrlen_base((long long)n, 10);
	if (flags->plus || flags->space || flags->negative)
		bw++;
	if (e)
		bw += 4;
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
		if (flags->zero_padding && flags->signed_state != 2)
			write(1, "0", 1);
		else if (!flags->left_justify && flags->signed_state != 2)
			write(1, " ", 1);
		bw++;
	}
	return (bw);
}

static void	write_float_unsigned(t_printf_flags *flags, long double n,
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
	if ((precision = flags->precision))
	{
		write(1, ".", 1);
		while (precision--)
		{
			n = (n - (long long)n) * 10.0;
			ft_putnbr_base((long long)n, 10, 0);
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

static int	write_float(t_printf_flags *flags, long double n, t_bool e)
{
	int			bw;
	int			s;

	if (!flags->use_precision)
	{
		flags->use_precision = 1;
		flags->precision = 6;
	}
	if ((flags->negative = n < 0.0))
		n = -n;
	s = 0;
	while (e && n != 0.0 && (n >= 10.0 || n < 1.0))
	{
		s += (n < 1.0) ? 1 : -1;
		n *= (n < 1.0) ? 10.0 : 0.1;
	}
	n = round_float(n, flags->precision);
	flags->signed_state = 1;
	bw = pad_float(flags, n, e, (s < 0) ? -s : s);
	if (!flags->left_justify)
		flags->signed_state = 2;
	write_float_unsigned(flags, n, e, s);
	if (!(flags->left_justify = !flags->left_justify))
		pad_float(flags, n, e, (s < 0) ? -s : s);
	return (bw);
}

int			float_writer(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strcmp(type, "Lf") == 0 || ft_strcmp(type, "LF") == 0)
		return (write_float(flags, va_arg(*args, long double), 0));
	if (ft_strchr(type, 'f') || ft_strchr(type, 'F'))
		return (write_float(flags, va_arg(*args, double), 0));
	if (ft_strcmp(type, "Le") == 0)
		return (write_float(flags, va_arg(*args, long double), 1));
	if (ft_strchr(type, 'e'))
		return (write_float(flags, va_arg(*args, double), 1));
	if (ft_strcmp(type, "LE") == 0)
		return (write_float(flags, va_arg(*args, long double), 2));
	if (ft_strchr(type, 'E'))
		return (write_float(flags, va_arg(*args, double), 2));
	if (ft_strcmp(type, "Lg") == 0)
		return (write_float_cmp(flags, va_arg(*args, long double), 1));
	if (ft_strchr(type, 'g'))
		return (write_float_cmp(flags, va_arg(*args, double), 1));
	if (ft_strcmp(type, "LG") == 0)
		return (write_float_cmp(flags, va_arg(*args, long double), 2));
	if (ft_strchr(type, 'G'))
		return (write_float_cmp(flags, va_arg(*args, double), 2));
	return (float_writer_hex(flags, args, type));
}
