#include "ft_42sh.h"

/*
**	clear_and_update_term()
**
**	If the user pressed the up/down arrow then we need to clear the current
**	text in the terminal.
**
**	1) If the user's cursor is not at the end of the curr text, move it there
**	2) Erase text on screen (amount of text is specified by e->buff_end)
**	3) Now we can bzero the buffer
**	4) cpy the contents of the history cmd into the buffer
**	5) set our cursor position and buffer_end to the size of the history cmd
**	6) Print the updated e->buffer to show it on screen.
*/

static	void		clear_and_update_term(t_env *e, char *curr_term,
								t_dl_list *curr_cmd, char **orig_term)
{
	size_t	i;

	while (e->cursor++ < e->buffer_end)
		ft_printf(" ");
	i = 0;
	while (i++ < e->buffer_end)
		ft_printf("\b \b");
	ft_bzero(e->buffer, e->buffer_end + 1);
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
**
**	UP arrow calls get_cmd_history() with mode = 0
**	DOWN arrow calls with mode = 1
**
**	If the user has previously typed something in the terminal before
**	pressing the UP or DOWN arrows, we need to remember what that text was so
**	we can restore it if they DOWN arrow all the way to the end of the history.
*/

void				get_cmd_history(t_env *e, int mode)
{
	static char			*orig_term = NULL;
	char				*curr_term;

	if (!(e->history_pos))
	{
		if (!mode)
		{
			if (orig_term)
				free(orig_term);
			orig_term = ft_strdup(e->buffer);
			e->history_pos = e->history_end;
		}
		else
			return ;
	}
	else if (mode == 1)
		e->history_pos = e->history_pos->next;
	else if (e->history_pos->prev)
		e->history_pos = e->history_pos->prev;
	if (!(e->history_pos))
		curr_term = orig_term;
	else
		curr_term = (char *)e->history_pos->content;
	clear_and_update_term(e, curr_term, e->history_pos, &orig_term);
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

	//ft_printf("|%s| %d\n", e->buffer, e->buffer_end);
	if ((node = ft_dl_lstnew(e->buffer, ft_strlen(e->buffer) + 1)))
	{
		ft_dl_lst_add_last(&(e->cmd_history), node);
		e->history_end = node;
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
	char		*content;
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
		{
			ft_printf("%5d  ", i);
			content = node->content;
			while (*content)
			{
				if (*content == '\n')
					ft_putstr("\\n");
				else if (*content == '\t')
					ft_putstr("\\t");
				else if (*content == '\r')
					ft_putstr("\\r");
				else if (*content == '\v')
					ft_putstr("\\v");
				else if (*content == '\f')
					ft_putstr("\\f");
				else
					ft_putchar(*content);
				content++;
			}
			ft_putchar('\n');
		}
		i++;
		node = node->next;
	}
}
