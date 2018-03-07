/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 00:47:08 by ashih             #+#    #+#             */
/*   Updated: 2018/02/02 19:57:09 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_puterror(char *message, char *term, int ret)
{
	if (term)
		ft_printf("{poop} Error: [%s] %s\n", term, message);
	else
		ft_printf("{poop} Error: %s\n", message);
	return (ret);
}
