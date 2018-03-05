/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:31:08 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:09 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

typedef struct	s_printf_flags
{
	t_bool		num_prepend;
	t_bool		zero_padding;
	t_bool		space;
	t_bool		left_justify;
	t_bool		plus;
	int			width;
	t_bool		use_precision;
	int			precision;

	int			signed_state;
	t_bool		negative;
	t_bool		p;
}				t_printf_flags;

int				string_writer(t_printf_flags *f, char *s);
int				char_writer(t_printf_flags *f, char c);
int				wstring_writer(t_printf_flags *f, wchar_t *s);
int				wchar_writer(t_printf_flags *f, wchar_t c);

long double		round_float(long double f, int p);
int				strip_zero(long double n, int m, long double b);
int				float_writer(t_printf_flags *f, va_list *a, char *t);
int				float_writer_hex(t_printf_flags *f, va_list *a, char *t);
int				write_float_cmp(t_printf_flags *f, long double n, t_bool e);

int				unsigned_writer(t_printf_flags *f, unsigned long long n,
		int b, t_bool u);
int				signed_writer(t_printf_flags *f, long long n);

int				ft_printf_writer(t_printf_flags *f, va_list *a, char *t);
t_bool			ft_printf_color(const char **f);
t_bool			ft_printf_font(const char **f);

int				jz_handler(t_printf_flags *f, va_list *a, char *t);
int				ll_handler(t_printf_flags *f, va_list *a, char *t);
int				l_handler(t_printf_flags *f, va_list *a, char *t);
int				h_handler(t_printf_flags *f, va_list *a, char *t);
int				hh_handler(t_printf_flags *f, va_list *a, char *t);

#endif
