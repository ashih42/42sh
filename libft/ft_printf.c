/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

static void	precision(const char **format, va_list *args, t_printf_flags *flags)
{
	if ((flags->use_precision = **format == '.'))
	{
		(*format)++;
		if (**format == '*')
		{
			flags->precision = va_arg(*args, int);
			flags->use_precision = (flags->precision >= 0);
			if (flags->precision < 0)
				flags->precision = 0;
			(*format)++;
		}
		else if (ft_isdigit(**format))
		{
			flags->precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else
			flags->precision = 0;
	}
}

static void	flag_info(const char **format, va_list *args, t_printf_flags *flags)
{
	while (**format == '#' || **format == ' ' || **format == '-' ||
			**format == '+' || **format == '*' || ft_isdigit(**format))
	{
		flags->num_prepend |= (**format == '#');
		flags->zero_padding |= (**format == '0');
		flags->space |= (**format == ' ');
		flags->left_justify |= (**format == '-');
		flags->plus |= (**format == '+');
		if (**format == '*')
		{
			flags->width = va_arg(*args, int);
			flags->left_justify |= (flags->width < 0);
			if (flags->width < 0)
				flags->width = -flags->width;
		}
		if (**format != '0' && ft_isdigit(**format))
		{
			flags->width = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else
			(*format)++;
	}
	precision(format, args, flags);
}

/*
**	int = 4 bytes
**	char = 1 byte
**	(int) = (char) (char) (char) (char)
**	push -> ft_memcpy -> pop -> return
*/

static int	get_type(const char **format)
{
	size_t	i;
	int		type;

	i = 0;
	type = 0;
	if ((*format)[i] == 'h' || (*format)[i] == 'l' || (*format)[i] == 'j' ||
			(*format)[i] == 'z' || (*format)[i] == 'L')
		i++;
	if (i == 1 && (((*format)[i - 1] == 'h' && (*format)[i] == 'h') ||
			((*format)[i - 1] == 'l' && (*format)[i] == 'l')))
		i++;
	if ((*format)[i] == 's' || (*format)[i] == 'S' || (*format)[i] == 'p' ||
			(*format)[i] == 'd' || (*format)[i] == 'D' || (*format)[i] == 'i' ||
			(*format)[i] == 'o' || (*format)[i] == 'O' || (*format)[i] == 'u' ||
			(*format)[i] == 'U' || (*format)[i] == 'x' || (*format)[i] == 'X' ||
			(*format)[i] == 'c' || (*format)[i] == 'C' || (*format)[i] == 'n' ||
			(*format)[i] == 'f' || (*format)[i] == 'F' || (*format)[i] == 'a' ||
			(*format)[i] == 'A' || (*format)[i] == 'e' || (*format)[i] == 'E' ||
			(*format)[i] == 'g' || (*format)[i] == 'G')
		ft_memcpy(&type, *format, ++i);
	(*format) += i;
	return (type);
}

/*
**	PRINTF PARSER DEBUGGING:
**	printf("flags parsed:\n");
**	printf("prepend number prefix:\t%d\n", flags.num_prepend);
**	printf("zero padding:\t\t%d\n", flags.zero_padding);
**	printf("space padding:\t\t%d\n", flags.space);
**	printf("left justify:\t\t%d\n", flags.left_justify);
**	printf("use + on positives:\t%d\n", flags.plus);
**	printf("width:\t\t\t%d\n", flags.width);
**	printf("precision:\t\t%d\n", flags.precision);
**	printf("type:\t\t\t%s\n\n", (char *)&type);
*/

static int	format_info(const char **format, va_list *args)
{
	t_printf_flags	flags;
	int				type;

	ft_bzero(&flags, sizeof(t_printf_flags));
	flag_info(format, args, &flags);
	type = get_type(format);
	if (type == 0)
	{
		if (**format)
			return (char_writer(&flags, *(*format)++));
		return (0);
	}
	if (ft_strchr((char *)&type, 'n'))
		return (0);
	return (ft_printf_writer(&flags, args, (char *)&type));
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		bw;

	va_start(args, format);
	bw = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			bw += format_info(&format, &args);
			if (*(format - 1) == 'n')
				*(va_arg(args, int *)) = bw;
		}
		else if (*format != '{' || !ft_printf_color(&format))
		{
			write(1, format++, 1);
			bw++;
		}
	}
	va_end(args);
	return (bw);
}
