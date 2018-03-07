/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:11:41 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 02:30:08 by apuel            ###   ########.fr       */
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
	ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	del_and_gnl(0, &(e->buffer));
}
