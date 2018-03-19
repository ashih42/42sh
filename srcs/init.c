/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:06:44 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 21:50:53 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_init()
**
**	This function should read in the default shell environment variables
**	(**envp) and load them into our 42sh environment variable data structure...
**
**	Essentially deserialize envp.
*/

void				sh_init(t_env *e, char **envp)
{
	char			*tmp_key;
	char			*tmp_val;
	char			*eq_ptr;

	while (*envp)
		if ((eq_ptr = ft_strchr(*envp, '=')))
		{
			if ((tmp_key = ft_strsub(*envp, 0, eq_ptr - (*envp))) &&
					(tmp_val = ft_strdup(eq_ptr + 1)))
			{
				set_variable(e, tmp_key, tmp_val);
				free(tmp_val);
				free(tmp_key);
			}
			envp++;
		}
	if ((tmp_val = getcwd(NULL, 0)))
	{
		set_variable(e, "PWD", tmp_val);
		if (!get_variable(e, "OLDPWD"))
			set_variable(e, "OLDPWD", tmp_val);
		free(tmp_val);
	}
}
