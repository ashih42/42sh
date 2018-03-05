/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	PRINTF TYPE CHART:
**	d/i - int
**	u - unsigned int
**	o - octal based unsigned int
**	x/X - hex based unsigned int
**	c - int (char representation)
**	s - char * (string representation)
**	p - void * (hexidecimal (x) representaion)
**	hhd/hhi - signed char
**	hhu - unsigned char
**	hho - octal based unsigned char
**	hhx/hX - hex based unsigned char
**	hd/hi - signed short int
**	hu - unsigned short int
**	ho - octal based unsigned short int
**	hx/hX - hex based unsigned short int
**	ld/li/D - long int
**	lu/U - unsigned long int
**	lo/O - octal based unsigned long int
**	lx/lX - hex based unsigned long int
**	lc/C - int (wchar_t representation)
**	ls/S - wchar_t * (string representaion)
**	lld/lli - long long int
**	llu - unsigned long long int
**	llo - octal based unsigned long long int
**	llx/llX - hex based unsigned long long int
**	jd/ji - signed intmax_t
**	ju - uintmax_t
**	jo - octal based uintmax_t
**	jx/jX - hex based uintmax_t
**	zd/zi/zu - size_t
**	zo - octal based size_t
**	zx/zX - hex based size_t
*/

static int	pad_number(t_printf_flags *flags, unsigned long long n, int base)
{
	int	bw;

	bw = (n != 0 || !flags->use_precision) ? ft_nbrlen_base(n, base) : 0;
	bw = (bw < flags->precision) ? flags->precision : bw;
	flags->precision = bw;
	if ((n != 0 || flags->p) && base == 16 && (flags->num_prepend || flags->p))
		bw += 2;
	if ((n != 0 || flags->use_precision) && base == 8 && flags->num_prepend)
		bw++;
	if (flags->signed_state && (flags->plus || flags->space || flags->negative))
		bw++;
	flags->zero_padding = (!flags->left_justify && flags->zero_padding);
	if (bw < flags->width && flags->zero_padding && !flags->use_precision)
	{
		flags->precision += flags->width - bw;
		bw = flags->width;
	}
	while (bw < flags->width)
	{
		if (!flags->left_justify && flags->signed_state != 2)
			write(1, " ", 1);
		bw++;
	}
	return (bw);
}

int			unsigned_writer(t_printf_flags *flags, unsigned long long n,
	int base, t_bool u)
{
	int		bw;
	size_t	len;

	bw = pad_number(flags, n, base);
	if (n != 0 && base == 16 && flags->num_prepend && u)
		write(1, "0X", 2);
	if ((n != 0 || flags->p) && base == 16 &&
			(flags->num_prepend || flags->p) && !u)
		write(1, "0x", 2);
	if ((n != 0 || flags->use_precision) && base == 8 && flags->num_prepend)
		write(1, "0", 1);
	len = ft_nbrlen_base(n, base);
	while (len++ < (size_t)flags->precision)
		write(1, "0", 1);
	if (n != 0 || !flags->use_precision || flags->precision)
		ft_putnbr_base(n, base, u);
	if (flags->left_justify)
	{
		flags->left_justify = 0;
		pad_number(flags, n, base);
	}
	return (bw);
}

int			signed_writer(t_printf_flags *flags, long long n)
{
	if ((flags->negative = n < 0))
		n = -n;
	flags->signed_state = 1;
	pad_number(flags, n, 10);
	if (!flags->left_justify)
		flags->signed_state = 2;
	if (flags->negative)
		write(1, "-", 1);
	else if (flags->plus)
		write(1, "+", 1);
	else if (flags->space)
		write(1, " ", 1);
	return (unsigned_writer(flags, n, 10, 0));
}

static int	default_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (type[0] == 'l')
		return (l_handler(flags, args, type));
	if (ft_strncmp(type, "hh", 2) == 0)
		return (hh_handler(flags, args, type));
	if (type[0] == 'h')
		return (h_handler(flags, args, type));
	if (type[0] == 'j' || type[0] == 'z')
		return (jz_handler(flags, args, type));
	if (ft_strchr(type, 'u'))
		return (unsigned_writer(flags, va_arg(*args, unsigned int), 10, 0));
	if (ft_strchr(type, 'o'))
		return (unsigned_writer(flags, va_arg(*args, unsigned int), 8, 0));
	if (ft_strchr(type, 'x'))
		return (unsigned_writer(flags, va_arg(*args, unsigned int), 16, 0));
	if (ft_strchr(type, 'X'))
		return (unsigned_writer(flags, va_arg(*args, unsigned int), 16, 1));
	return (signed_writer(flags, va_arg(*args, int)));
}

int			ft_printf_writer(t_printf_flags *flags, va_list *args, char *type)
{
	int	result;

	result = float_writer(flags, args, type);
	if (result != -42)
		return (result);
	if (ft_strchr(type, 'p'))
	{
		flags->p = 1;
		return (unsigned_writer(flags,
				va_arg(*args, unsigned long long), 16, 0));
	}
	if (ft_strchr(type, 'D') || ft_strchr(type, 'U') || ft_strchr(type, 'O') ||
			ft_strchr(type, 'C') || ft_strchr(type, 'S') ||
			ft_strcmp(type, "lc") == 0 || ft_strcmp(type, "ls") == 0)
		return (l_handler(flags, args, type));
	if (ft_strchr(type, 'c'))
		return (char_writer(flags, (char)va_arg(*args, int)));
	if (ft_strchr(type, 's'))
		return (string_writer(flags, va_arg(*args, char *)));
	if (ft_strncmp(type, "ll", 2) == 0)
		return (ll_handler(flags, args, type));
	return (default_handler(flags, args, type));
}
