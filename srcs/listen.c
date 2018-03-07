/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:11:41 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 17:58:37 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_listen()
**
**	This function should implement listening on stdin. Will need to read
**	one char at a time so that backspaces and tabs will be supported!!!
**
**	Because the input is of an unspecified length, we will either need to
**	realloc when we are about to go over our allocation limit or use some
**	sort of linked list implementation...
*/


void	sh_listen(t_env *e)
{
	ft_bzero(e->buffer, BUFFER_SIZE + 1);
	e->pos = 0;

	ft_printf("{robot} %s > ", e->pwd);

	char c;
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		e->buffer[e->pos++] = c;
//		ft_putchar(c);
		if (c == '\n')
		{
//			ft_printf("{robot}beep boop beep boop{robot}\n");
			return ;
		}
		
	}
	

}
