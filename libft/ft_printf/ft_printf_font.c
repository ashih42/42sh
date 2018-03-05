/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_font.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_bool	ft_printf_bg_color(const char **format)
{
	int	color;
	int	i;

	if (ft_strncmp(*format, "{bg:", 4) == 0)
	{
		if (ft_isdigit((*format)[4]))
		{
			color = ft_atoi(*format + 4);
			if (color >= 0 && color <= 256)
			{
				i = 0;
				while (ft_isdigit((*format)[4 + i]))
					i++;
				if ((*format)[4 + i] == '}')
				{
					*format += 4 + i + 1;
					ft_putstr("\x1B[48;5;");
					ft_putnbr(color);
					ft_putchar('m');
					return (1);
				}
			}
		}
	}
	return (0);
}

static t_bool	ft_printf_fg_color(const char **format)
{
	int	color;
	int	i;

	if (ft_strncmp(*format, "{fg:", 4) == 0)
	{
		if (ft_isdigit((*format)[4]))
		{
			color = ft_atoi(*format + 4);
			if (color >= 0 && color <= 256)
			{
				i = 0;
				while (ft_isdigit((*format)[4 + i]))
					i++;
				if ((*format)[4 + i] == '}')
				{
					*format += 4 + i + 1;
					ft_putstr("\x1B[38;5;");
					ft_putnbr(color);
					ft_putchar('m');
					return (1);
				}
			}
		}
	}
	return (ft_printf_bg_color(format));
}

static t_bool	ft_printf_font_ext(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{dim}", 5) == 0)))
	{
		*format += 5;
		ft_putstr("\x1B[2m");
	}
	else if ((result = (ft_strncmp(*format, "{hidden}", 8) == 0)))
	{
		*format += 8;
		ft_putstr("\x1B[8m");
	}
	if ((result = (ft_strncmp(*format, "{invert}", 8) == 0)))
	{
		*format += 8;
		ft_putstr("\x1B[7m");
	}
	else
		return (ft_printf_fg_color(format));
	return (result);
}

t_bool			ft_printf_font(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{reset}", 7) == 0)))
	{
		*format += 7;
		ft_putstr("\x1B[0m");
	}
	else if ((result = (ft_strncmp(*format, "{bold}", 6) == 0)))
	{
		*format += 6;
		ft_putstr("\x1B[1m");
	}
	else if ((result = (ft_strncmp(*format, "{underline}", 11) == 0)))
	{
		*format += 11;
		ft_putstr("\x1B[4m");
	}
	else if ((result = (ft_strncmp(*format, "{blink}", 7) == 0)))
	{
		*format += 7;
		ft_putstr("\x1B[5m");
	}
	else
		return (ft_printf_font_ext(format));
	return (result);
}
