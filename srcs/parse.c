#include "ft_42sh.h"

/*
**	sh_parse()
**
**	This function will take the input read in via sh_listen() and parse it for
**	redirections, escaped characters, etc.
*/



void	append_terms(t_list **list, char **terms)
{
	int i;
	i = -1;
	while (terms[++i])
	{
		ft_lst_add_last(list, ft_lstnew(terms[i], ft_strlen(terms[i]) + 1));
	}
//	ft_char_array_del(terms);
}

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

char	**sh_parse(t_env *e)
{

/*	
	ft_printf("e->buffer: %s\n", e->buffer);
	char **args = split_argv(e->buffer, WHITESPACE);
	char **terms;
	t_list *list = 0;

	int i = -1;
	while (args[++i])
	{
		ft_printf("i = %d, args[i] = %s\n", i, args[i]);
		terms = str_explode(args[i], DELIM);
		ft_printf("wut happened\n");
//		append_terms(&list, terms);
	}
*/
//	ft_char_array_del(args);
/*
	char **all_terms = list_to_array(list);
	ft_printf("str_explode:\n");
	ft_print_char_array(all_terms);
*/
//	ft_printf("e->buffer: %s\n", e->buffer);
	

	return (split_argv(e->buffer, WHITESPACE));

}
