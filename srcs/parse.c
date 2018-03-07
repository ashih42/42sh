/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:40 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 01:51:11 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_parse()
**
**	This function will take the input read in via sh_listen() and parse it for
**	redirections, escaped characters, etc.
*/

char	**sh_parse(t_env *e, int *argc)
{
	return (split_argv(e->buffer, WHITESPACE, argc));
}
