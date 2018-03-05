/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:52:18 by apuel             #+#    #+#             */
/*   Updated: 2017/12/02 11:56:18 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt_r(int n)
{
	int i;

	if (n < 0)
		return (0);
	i = n % 2;
	while (i * i < n)
		i += 2;
	return (i);
}