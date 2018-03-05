/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:58:44 by apuel             #+#    #+#             */
/*   Updated: 2017/12/14 22:58:45 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

unsigned char	*ft_readstdin(size_t *size)
{
	unsigned char	buffer[4096];
	unsigned char	*temp;
	unsigned char	*input;
	int				br;

	input = (unsigned char *)0;
	if (size)
	{
		*size = 0;
		while ((br = read(0, buffer, 4096)) > 0)
		{
			temp = malloc(*size + br + 1);
			if (temp && input)
				ft_memcpy(temp, input, *size);
			if (input)
				free(input);
			input = temp;
			if (!input)
				break ;
			ft_memcpy(input + *size, buffer, br);
			*size += br;
			input[*size] = '\0';
		}
	}
	return (input);
}
