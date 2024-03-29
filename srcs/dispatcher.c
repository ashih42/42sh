/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 06:17:48 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:22:23 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_dispatcher()
**
**	This function should take the cmds/arguments that the parser has identified:
**
**	1) Check if the command is a local one (i.e. builtin)
**	2) If it's not local, check if the cmd is located in PATH env folders
**	3) If the cmd is not located in the specified PATHS check if the the cmd was
**	   provided as a literal path.
*/

static void		wait_all_pids(t_env *e, t_dsp *d)
{
	while (d->pids)
	{
		waitpid(d->pids->content_size, &(d->status), 0);
		d->pids = d->pids->next;
	}
	ft_lstdel(&(e->children_pids), NULL);
}

static void		dsp_checks(t_env *e, t_dsp *d)
{
	if (!built_ins(e, ft_char_array_length(d->argv), d->argv, &(d->status)))
	{
		if ((d->envp = serialize_envp(e)))
		{
			if (execute(e, d->argv, d->envp, &(d->status)) < 0)
				d->status = -1;
			ft_char_array_del(d->envp);
		}
		else
		{
			ft_printf("42sh: failed to allocate memory for envp\n");
			d->status = -1;
		}
	}
	if (!(e->pipe) && (d->pids = e->children_pids))
	{
		wait_all_pids(e, d);
		if (WIFEXITED(d->status))
			d->status = WEXITSTATUS(d->status);
		else
			d->status = -1;
	}
}

static void		dsp_loop(t_env *e, char ***cmds, t_dsp *d)
{
	while (cmds[++(d->i)])
	{
		d->argv = cmds[d->i];
		if (d->i > 0)
		{
			if (d->argv[0][0] == ';')
				continue ;
			if (!ft_strcmp(d->argv[0], "||"))
			{
				if (!d->status)
					break ;
				continue ;
			}
			if (!ft_strcmp(d->argv[0], "&&"))
			{
				if (d->status)
					break ;
				continue ;
			}
		}
		setup_pipes(e, cmds, &(d->i));
		dsp_checks(e, d);
		e->pipe = 0;
	}
}

void			sh_dispatcher(t_env *e, char ***cmds)
{
	t_dsp	d;
	size_t	i;

	d.status = 0;
	d.i = -1;
	e->fd = -1;
	e->redir_out = -1;
	dsp_loop(e, cmds, &d);
	e->pipe = 0;
	if (e->fd != -1)
		close(e->fd);
	if (e->redir_out != -1)
		close(e->redir_out);
	d.pids = e->children_pids;
	wait_all_pids(e, &d);
	i = -1;
	while (cmds[++i])
		ft_char_array_del(cmds[i]);
	free(cmds);
}
