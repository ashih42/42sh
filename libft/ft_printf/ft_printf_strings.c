/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_length(t_printf_flags *flags, void **str, t_bool wchar)
{
	size_t	len;

	if (*str == (void *)0)
		*str = wchar ? (void *)L"(null)" : (void *)"(null)";
	if (wchar)
		len = ft_wstrlen((wchar_t *)(*str));
	else
		len = ft_strlen((char *)(*str));
	if (flags->use_precision && len > (size_t)flags->precision)
		len = flags->precision;
	return (len);
}

int				string_writer(t_printf_flags *flags, char *str)
{
	int		bw;
	size_t	len;

	len = get_length(flags, (void **)&str, 0);
	bw = len;
	if (!flags->left_justify)
		while (bw < flags->width)
		{
			if (flags->zero_padding)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			bw++;
		}
	ft_putstrn(str, len);
	if (flags->left_justify)
		while (bw < flags->width)
		{
			write(1, " ", 1);
			bw++;
		}
	return (bw);
}

int				char_writer(t_printf_flags *flags, char c)
{
	int		bw;

	bw = 1;
	if (!flags->left_justify)
		while (bw < flags->width)
		{
			if (flags->zero_padding)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			bw++;
		}
	ft_putchar(c);
	if (flags->left_justify)
		while (bw < flags->width)
		{
			write(1, " ", 1);
			bw++;
		}
	return (bw);
}

int				wstring_writer(t_printf_flags *flags, wchar_t *str)
{
	int		bw;
	size_t	len;

	len = get_length(flags, (void **)&str, 1);
	bw = len;
	if (!flags->left_justify)
		while (bw < flags->width)
		{
			if (flags->zero_padding)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			bw++;
		}
	ft_putwstrn(str, len);
	if (flags->left_justify)
		while (bw < flags->width)
		{
			write(1, " ", 1);
			bw++;
		}
	return (bw);
}

int				wchar_writer(t_printf_flags *flags, wchar_t c)
{
	int		bw;

	bw = 1;
	if (!flags->left_justify)
		while (bw < flags->width)
		{
			if (flags->zero_padding)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			bw++;
		}
	ft_putwchar(c);
	if (flags->left_justify)
		while (bw < flags->width)
		{
			write(1, " ", 1);
			bw++;
		}
	return (bw);
}
