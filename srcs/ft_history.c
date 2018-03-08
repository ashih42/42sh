/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:40:20 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 16:49:34 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	add_cmd_history()
**
**	This function is called after a builtin or 'execute' call.
**
**	It will initialize [cmd_count, e->buffer] as the contents of lst node.
**	The node then gets added to the end of the e->cmd_history linked list.
*/

int		add_cmd_history(t_env *e)
{
	static int	cmd_count = 1;
	char		*ind;
	t_list		*node;

	ind = ft_itoa(cmd_count);
	if ((node = new_entry(ind, e->buffer)))
	{
		free(ind);
		ft_lst_add_last(&(e->cmd_history), node);
		cmd_count++;
		return (1);
	}
	return (0);
}

/*
**	ft_history()
**
**	Display the command history of our shell.
*/

// TODO:
// `history 5` should display commands from ind 5 onwards...


void	ft_history(t_env *e, int argc, char **argv)
{
	t_list	*node;
	char	**content;

	node = e->cmd_history;
	while (node)
	{
		content = node->content;
		ft_printf("%5s  %s\n", content[0], content[1]);
		node = node->next;
	}
}