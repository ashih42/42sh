/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:43:29 by nmei              #+#    #+#             */
/*   Updated: 2018/03/15 16:46:24 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}
