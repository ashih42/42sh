/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:47 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 17:42:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	init_sh()
**
**	This function should read in the default shell environment variables
**	(**envp) and load them into our 42sh environment variable data structure...
*/

void	init_sh(t_env *e, char **envp)
{
	(void)envp;

	e->pwd = getcwd(0, 0);
}