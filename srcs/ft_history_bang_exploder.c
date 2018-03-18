/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_bang_exploder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:06:44 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:21:52 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	history_bang_num_exploder()
**
**	Converts a number sequence after a bang (!) and uses it to try and find
**	the corresponding numbered history command.
*/

static int		history_bang_num_exploder(t_env *e, char *buf)
{
	t_dl_list	*cmd;
	int			indx;
	char		*content;

	indx = ft_atoi(buf);
	indx = (indx < 0) ? ft_dl_lst_size(e->cmd_history) + indx : indx - 1;
	if (indx >= 0 && (cmd = ft_dl_lst_at(e->cmd_history, indx)))
	{
		content = (char *)cmd->content;
		ft_bzero(e->buffer, e->buffer_size + 1);
		ft_memmove(e->buffer, content, ft_strlen(content));
		return (1);
	}
	ft_printf("42sh: no such event: %d\n", (indx > 0) ? indx : 0);
	return (-1);
}

/*
**	history_bang_str_exploder()
**
**	Converts a string sequence after a bang (!) and uses it to try and find
**	the last command that started with the same str.
*/

static int		history_bang_str_exploder(t_env *e, char *buf)
{
	t_dl_list	*curr;
	char		*last_content;
	char		*content;
	size_t		buf_len;

	last_content = NULL;
	curr = e->cmd_history;
	buf_len = ft_strlen(buf);
	while (curr)
	{
		content = (char *)curr->content;
		if (ft_strncmp(buf, content, buf_len) == 0)
			last_content = content;
		curr = curr->next;
	}
	if (last_content)
	{
		ft_bzero(e->buffer, e->buffer_size + 1);
		ft_memmove(e->buffer, last_content, ft_strlen(last_content));
		return (1);
	}
	ft_printf("42sh: event not found: %s\n", buf);
	return (-1);
}

/*
**	history_bang_exploder()
**
**	I can haz exploder too?
**
**	Call the '!#' (bang num) exploder if:
**
**	1) There is a character after the '!' AND
**	2a) There is a digit character after the '!' OR
**	2b) There is a '-'/'+' after '!' AND the character after '-'/'+' is a digit
**
**	Call the '!str' (bang str) exploder otherwise
**
**	The function:
**	Returns 0 if no bang (!) was found
**	Returns 1 if a bang (!) was successfully expanded
**	Returns -1 if a bang (!) expansion was unsuccessful
**
**	If a bang (!) lookup was successful then e->buffer will have the cmd string
**	that was looked up.
*/

int				history_bang_exploder(t_env *e)
{
	char		*buf;

	buf = e->buffer;
	if (*buf == '!')
	{
		buf++;
		if (*buf && (ft_isdigit(*buf) ||
		((*buf == '-' || *buf == '+') && *(buf + 1) && ft_isdigit(*(buf + 1)))))
			return (history_bang_num_exploder(e, buf));
		else
			return (history_bang_str_exploder(e, buf));
	}
	return (0);
}
