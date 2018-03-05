/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			jz_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strcmp(type, "ju") == 0)
		return (unsigned_writer(flags, va_arg(*args, uintmax_t), 10, 0));
	else if (ft_strcmp(type, "jo") == 0)
		return (unsigned_writer(flags, va_arg(*args, uintmax_t), 8, 0));
	else if (ft_strcmp(type, "jx") == 0)
		return (unsigned_writer(flags, va_arg(*args, uintmax_t), 16, 0));
	else if (ft_strcmp(type, "jX") == 0)
		return (unsigned_writer(flags, va_arg(*args, uintmax_t), 16, 1));
	else if (type[0] != 'z')
		return (signed_writer(flags, va_arg(*args, intmax_t)));
	else if (ft_strcmp(type, "zu") == 0)
		return (unsigned_writer(flags, va_arg(*args, size_t), 10, 0));
	else if (ft_strcmp(type, "zo") == 0)
		return (unsigned_writer(flags, va_arg(*args, size_t), 8, 0));
	else if (ft_strcmp(type, "zx") == 0)
		return (unsigned_writer(flags, va_arg(*args, size_t), 16, 0));
	else if (ft_strcmp(type, "zX") == 0)
		return (unsigned_writer(flags, va_arg(*args, size_t), 16, 1));
	else
		return (signed_writer(flags, va_arg(*args, size_t)));
}

int			ll_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strcmp(type, "llu") == 0)
		return (unsigned_writer(flags,
				va_arg(*args, unsigned long long), 10, 0));
	else if (ft_strcmp(type, "llo") == 0)
		return (unsigned_writer(flags,
				va_arg(*args, unsigned long long), 8, 0));
	else if (ft_strcmp(type, "llx") == 0)
		return (unsigned_writer(flags,
				va_arg(*args, unsigned long long), 16, 0));
	else if (ft_strcmp(type, "llX") == 0)
		return (unsigned_writer(flags,
				va_arg(*args, unsigned long long), 16, 1));
	else
		return (signed_writer(flags, va_arg(*args, long long)));
}

int			l_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strchr(type, 'U') || ft_strcmp(type, "lu") == 0)
		return (unsigned_writer(flags, va_arg(*args, unsigned long), 10, 0));
	else if (ft_strchr(type, 'O') || ft_strcmp(type, "lo") == 0)
		return (unsigned_writer(flags, va_arg(*args, unsigned long), 8, 0));
	else if (ft_strcmp(type, "lx") == 0)
		return (unsigned_writer(flags, va_arg(*args, unsigned long), 16, 0));
	else if (ft_strcmp(type, "lX") == 0)
		return (unsigned_writer(flags, va_arg(*args, unsigned long), 16, 1));
	else if (ft_strchr(type, 'C') || ft_strcmp(type, "lc") == 0)
		return (wchar_writer(flags, (wchar_t)va_arg(*args, wint_t)));
	else if (ft_strchr(type, 'S') || ft_strcmp(type, "ls") == 0)
		return (wstring_writer(flags, va_arg(*args, wchar_t *)));
	return (signed_writer(flags, va_arg(*args, long)));
}

int			h_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strcmp(type, "hu") == 0)
		return (unsigned_writer(flags,
				(unsigned short)va_arg(*args, int), 10, 0));
	else if (ft_strcmp(type, "ho") == 0)
		return (unsigned_writer(flags,
				(unsigned short)va_arg(*args, int), 8, 0));
	else if (ft_strcmp(type, "hx") == 0)
		return (unsigned_writer(flags,
				(unsigned short)va_arg(*args, int), 16, 0));
	else if (ft_strcmp(type, "hX") == 0)
		return (unsigned_writer(flags,
				(unsigned short)va_arg(*args, int), 16, 1));
	else
		return (signed_writer(flags, (short)va_arg(*args, int)));
}

int			hh_handler(t_printf_flags *flags, va_list *args, char *type)
{
	if (ft_strcmp(type, "hhu") == 0)
		return (unsigned_writer(flags,
				(unsigned char)va_arg(*args, int), 10, 0));
	else if (ft_strcmp(type, "hho") == 0)
		return (unsigned_writer(flags,
				(unsigned char)va_arg(*args, int), 8, 0));
	else if (ft_strcmp(type, "hhx") == 0)
		return (unsigned_writer(flags,
				(unsigned char)va_arg(*args, int), 16, 0));
	else if (ft_strcmp(type, "hhX") == 0)
		return (unsigned_writer(flags,
				(unsigned char)va_arg(*args, int), 16, 1));
	else
		return (signed_writer(flags, (char)va_arg(*args, int)));
}
