/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:30:58 by apuel             #+#    #+#             */
/*   Updated: 2017/12/05 17:31:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void		ft_putnbr_base(unsigned long long nbr, int base, t_bool u)
{
	if (nbr / base != 0)
		ft_putnbr_base(nbr / base, base, u);
	if (u)
		ft_putchar(("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")[nbr % base]);
	else
		ft_putchar(("0123456789abcdefghijklmnopqrstuvwxyz")[nbr % base]);
}
