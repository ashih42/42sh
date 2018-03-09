#include "ft_42sh.h"

static	void		clear_and_update_term(t_env *e, char *curr_term,
								t_dl_list *curr_cmd, char **orig_term)
{
	size_t	i;

	i = 0;
	while (i++ < e->buffer_end)
		ft_printf("\b \b");
	ft_bzero(e->buffer, e->buffer_size + 1);
	i = ft_strlen(curr_term);
	ft_memmove(e->buffer, curr_term, i);
	e->cursor = i;
	e->buffer_end = i;
	ft_printf("%s", e->buffer);
	if (curr_cmd == NULL)
	{
		free(*orig_term);
		*orig_term = NULL;
	}
}

/*
**	get_cmd_history()
*/

//	Known issues:
//	Changing position of cursor then pressing up/down arrows fucks shit up...

void				get_cmd_history(t_env *e, int mode)
{
	static char	*orig_term = NULL;
	t_dl_list	*curr_cmd;
	char		*curr_term;

	if (e->history_pos == -1)
	{
		if (orig_term)
			free(orig_term);
		orig_term = strdup(e->buffer);
		e->history_pos = ft_dl_lst_size(e->cmd_history);
	}
	e->history_pos = (mode == 1) ? e->history_pos + 1 : e->history_pos - 1;
	e->history_pos = (e->history_pos < 0) ? 0 : e->history_pos;
	curr_cmd = ft_dl_lst_at(e->cmd_history, e->history_pos);
	if (curr_cmd == NULL)
	{
		curr_term = orig_term;
		e->history_pos = -1;
	}
	else
		curr_term = (char *)curr_cmd->content;
	clear_and_update_term(e, curr_term, curr_cmd, &orig_term);
}

/*
**	add_cmd_history()
**
**	This function is called after a builtin or 'execute' call.
**
**	It will initialize 'e->buffer' as the contents of lst node.
**	The node then gets added to the end of the e->cmd_history linked list.
*/

int					add_cmd_history(t_env *e)
{
	t_dl_list		*node;

	if ((node = ft_dl_lstnew(e->buffer, ft_strlen(e->buffer) + 1)))
	{
		ft_dl_lst_add_last(&(e->cmd_history), node);
		return (1);
	}
	return (0);
}

/*
**	ft_history()
**
**	Display the command history of our shell.
*/

void				ft_history(t_env *e, int argc, char **argv)
{
	t_dl_list	*node;
	char		**content;
	int			i;
	int			cmp;

	i = 1;
	cmp = 1;
	node = e->cmd_history;
	if (argc > 1)
		cmp = ft_atoi(argv[1]);
	if (cmp < 0)
		cmp = ft_dl_lst_size(node) + cmp + 1;
	while (node)
	{
		if (cmp <= i)
			ft_printf("%5d  %s\n", i, node->content);
		i++;
		node = node->next;
	}
}
