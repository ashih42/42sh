#include "ft_42sh.h"

static t_dl_list	*ft_dl_lstnew(void const *content, size_t content_size)
{
	t_dl_list	*new;

	if ((new = malloc(sizeof(t_dl_list))))
	{
		if (content_size != 0 && (new->content = malloc(content_size)) == NULL)
		{
			free(new);
			return (NULL);
		}
		if (content)
		{
			ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
		}
		else
		{
			if (new->content != NULL)
				free(new->content);
			new->content = NULL;
			new->content_size = 0;
		}
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

static void			ft_dl_lst_add_last(t_dl_list **a_dl_lst, t_dl_list *new)
{
	t_dl_list	*prev;
	t_dl_list	*curr;

	if (new && a_dl_lst)
	{
		if (*a_dl_lst)
		{
			curr = *a_dl_lst;
			while (curr->next)
				curr = curr->next;
			new->prev = curr;
			curr->next = new;
		}
		else
			*a_dl_lst = new;
	}
}

static int			ft_dl_lst_size(t_dl_list *lst)
{
	int	total;

	total = 0;
	while (lst)
	{
		total++;
		lst = lst->next;
	}
	return (total);
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
