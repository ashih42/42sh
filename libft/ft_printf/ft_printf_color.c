/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_bool	ft_printf_color_ext_ext_ext(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{light_magenta}", 15) == 0)))
	{
		*format += 15;
		ft_putstr("\x1B[95m");
	}
	else if ((result = (ft_strncmp(*format, "{light_cyan}", 12) == 0)))
	{
		*format += 12;
		ft_putstr("\x1B[96m");
	}
	else if ((result = (ft_strncmp(*format, "{white}", 7) == 0)))
	{
		*format += 7;
		ft_putstr("\x1B[97m");
	}
	else if ((result = (ft_strncmp(*format, "{dark_gray}", 11) == 0)))
	{
		*format += 11;
		ft_putstr("\x1B[90m");
	}
	else
		return (ft_printf_font(format));
	return (result);
}

static t_bool	ft_printf_color_ext_ext(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{light_red}", 11) == 0)))
	{
		*format += 11;
		ft_putstr("\x1B[91m");
	}
	else if ((result = (ft_strncmp(*format, "{light_green}", 13) == 0)))
	{
		*format += 13;
		ft_putstr("\x1B[92m");
	}
	else if ((result = (ft_strncmp(*format, "{light_yellow}", 14) == 0)))
	{
		*format += 14;
		ft_putstr("\x1B[93m");
	}
	else if ((result = (ft_strncmp(*format, "{light_blue}", 12) == 0)))
	{
		*format += 12;
		ft_putstr("\x1B[94m");
	}
	else
		return (ft_printf_color_ext_ext_ext(format));
	return (result);
}

static t_bool	ft_printf_color_ext(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{magenta}", 9) == 0)))
	{
		*format += 9;
		ft_putstr("\x1B[35m");
	}
	else if ((result = (ft_strncmp(*format, "{cyan}", 6) == 0)))
	{
		*format += 6;
		ft_putstr("\x1B[36m");
	}
	else if ((result = (ft_strncmp(*format, "{gray}", 6) == 0)))
	{
		*format += 6;
		ft_putstr("\x1B[37m");
	}
	else if ((result = (ft_strncmp(*format, "{black}", 7) == 0)))
	{
		*format += 7;
		ft_putstr("\x1B[30m");
	}
	else
		return (ft_printf_color_ext_ext(format));
	return (result);
}

t_bool			ft_printf_color(const char **format)
{
	t_bool result;

	if ((result = (ft_strncmp(*format, "{red}", 5) == 0)))
	{
		*format += 5;
		ft_putstr("\x1B[31m");
	}
	else if ((result = (ft_strncmp(*format, "{green}", 7) == 0)))
	{
		*format += 7;
		ft_putstr("\x1B[32m");
	}
	else if ((result = (ft_strncmp(*format, "{yellow}", 8) == 0)))
	{
		*format += 8;
		ft_putstr("\x1B[33m");
	}
	else if ((result = (ft_strncmp(*format, "{blue}", 6) == 0)))
	{
		*format += 6;
		ft_putstr("\x1B[34m");
	}
	else
		return (ft_printf_color_ext(format));
	return (result);
}
