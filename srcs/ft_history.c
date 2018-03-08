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
	t_list		*node;

	if ((node = ft_lstnew(e->buffer, ft_strlen(e->buffer) + 1)))
	{
		ft_lst_add_last(&(e->cmd_history), node);
		return (1);
	}
	return (0);
}

/*
**	ft_history()
**
**	Display the command history of our shell.
*/

void	ft_history(t_env *e, int argc, char **argv)
{
	t_list	*node;
	char	**content;
	int		i;
	int		cmp;

	i = 1;
	cmp = 1;
	node = e->cmd_history;
	if (argc > 1)
		cmp = ft_atoi(argv[1]);
	if (cmp < 0)
		cmp = ft_lst_size(node) + cmp + 1;
	while (node)
	{
		if (cmp <= i)
			ft_printf("%5d  %s\n", i, node->content);
		i++;
		node = node->next;
	}
}
