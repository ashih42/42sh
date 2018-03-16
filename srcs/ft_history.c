#include "ft_42sh.h"

static	void		get_cmd_history_deux(t_env *e, char *curr_term,
								t_dl_list *curr_cmd, char **orig_term)
{
	clear_and_update_term(e, curr_term);
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
	static char	*orig_term = NULL;
	char		*curr_term;

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
	get_cmd_history_deux(e, curr_term, e->history_pos, &orig_term);
}

/*
**	add_cmd_history()
**
**	This function is called after a builtin or 'execute' call.
**
**	It will initialize 'e->buffer' as the contents of lst node.
**	The node then gets added to the end of the e->cmd_history linked list.
**
**	Function returns 1 if no new node was added.
**	Function returns 0 if new node was added successfully.
*/

int					add_cmd_history(t_env *e)
{
	t_dl_list	*node;

	if (!*e->buffer)
		return (1);
	if ((node = ft_dl_lstnew(e->buffer, ft_strlen(e->buffer) + 1)))
	{
		ft_dl_lst_add_last(&(e->cmd_history), node);
		e->history_end = node;
		return (0);
	}
	return (1);
}

/*
**	print_hidden()
**
**	prints hidden chars like '\n' '\t' '\r' '\v' '\f'
*/

static void			print_hidden(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			ft_putstr("\\n");
		else if (*str == '\t')
			ft_putstr("\\t");
		else if (*str == '\r')
			ft_putstr("\\r");
		else if (*str == '\v')
			ft_putstr("\\v");
		else if (*str == '\f')
			ft_putstr("\\f");
		else
			ft_putchar(*str);
		str++;
	}
	ft_putchar('\n');
}

/*
**	ft_history()
**
**	Display the command history of our shell.
*/

int					ft_history(t_env *e, int argc, char **argv)
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
			print_hidden(content);
		}
		i++;
		node = node->next;
	}
	return (0);
}
