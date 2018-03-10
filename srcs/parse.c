#include "ft_42sh.h"

/*
**	sh_parse()
**
**	This function will take the input read in via sh_listen() and parse it for
**	redirections, escaped characters, etc.
*/

// The commented out stuff is probably not needed, but let's keep them here for now :>
/*
// not sure if needed
char   **list_to_array(t_list *list)
{
	char **array = malloc(sizeof(char *) * (ft_lst_size(list) + 1));
	int i = 0;
	while (list != 0)
	{
		array[i++] = ft_strdup(list->content);
		list = list->next;
	}
	array[i] = 0;
	return (array);
}

char	*queue_to_str(t_list *queue)
{
	char *str = ft_strnew(0);
	char *temp;

	while (queue != 0)
	{
		temp = str;
		str = ft_strjoin(str, queue->content);
		ft_strdel(&temp);
		queue = queue->next;
	}
	return (str);
}

void	queue_op(t_list **list, t_list **queue, t_list **new_list)
{
	ft_printf("GOT HERE 1\n");
	
	*list = (*list)->next;
	while (*list != 0)
	{
		if (ft_strequ((*list)->content, "\""))
			break ;
	//	ft_printf("adding to queue: %s\n", (*list)->content);
		ft_lst_add_last(queue, ft_lst_new_ref((*list)->content, sizeof(char *)));
		*list = (*list)->next;
	}
	
	//	ft_printf("queue size = %d\n", ft_lst_size(*queue));
	ft_lst_add_last(new_list, ft_lst_new_ref(queue_to_str(*queue), sizeof(char *)));
}


// build and return a new linked list
t_list	*merge_quotes(t_list *list)
{
	t_list *queue = 0;
	t_list *new_list = 0;

	while (list != 0)
	{
		if (ft_strequ(list->content, "\""))
		{
			queue_op(&list, &queue, &new_list);
			queue = 0;
		}
		else
			ft_lst_add_last(&new_list, ft_lst_new_ref(list->content, sizeof(char *)));
		list = list->next;
	}
	if (ft_lst_size(queue) != 0)
	{
		ft_printf("DANGLING QUOTE MANG\n");
	}
	return (new_list);
}
*/

int 	is_operator(char *str)
{
	if (ft_strequ(str, "|"))
		return (1);
	else if (ft_strequ(str, ">"))
		return (2);
	else if (ft_strequ(str, ">>"))
		return (3);
	else if (ft_strequ(str, "<"))
		return (4);
	else
		return (0);
}

t_list	*list_to_expr(t_list *list)
{
	t_list *expr_list = 0;
	t_list *expr;

	while (list != 0)
	{
		if (is_operator(list->content))
		{
			expr = 0;
			ft_lst_add_last(&expr, ft_lst_new_ref(list->content, sizeof(char *)));
			ft_lst_add_last(&expr_list, ft_lst_new_ref(expr, sizeof(t_list *)));
			list = list->next;
		}
		else
		{
			expr = 0;
			while(list != 0)
			{
				if (is_operator(list->content))
					break ;
				ft_lst_add_last(&expr, ft_lst_new_ref(list->content, sizeof(char *)));
				list = list->next;
			}
			ft_lst_add_last(&expr_list, ft_lst_new_ref(expr, sizeof(t_list *)));
		}
	}
	return (expr_list);
}


char	**sh_parse(t_env *e)
{
	char **args = split_argv(e->buffer, WHITESPACE);
	t_list *list = 0;
	int i = -1;
	while (args[++i])
	{
		str_explode(args[i], &list);
	}
//	print_list(list);

//  fuck this shit
//	list = merge_quotes(list);
//	print_list(list);
	// this gets rid of whitespaces and then fails to add back whitespaces when merging the terms :'(

	t_list *expr_list = list_to_expr(list);
	print_expr_list(expr_list);

	return (split_argv(e->buffer, WHITESPACE));

}
