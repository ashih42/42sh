/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 21:56:18 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 19:20:13 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void			ft_democracy(t_env *e)
{
	ft_lstdel(&(e->files_head), (void (*)(void *, size_t))free);
	ft_lstdel(&(e->children_pids), NULL);
	ft_dl_lstdel(&(e->cmd_history), (void (*)(void *, size_t))free);
	ft_lstdel(&(e->envp), (void (*)(void *, size_t))ft_char_array_del);
	ft_strdel(&e->buffer);
}

int				ft_exit(t_env *e, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_democracy(e);
	exit(0);
	return (0);
}
