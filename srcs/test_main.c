#include <ft_42sh.h>

int matchparse(char *s1, char *s2);
int list_size(t_list *list);

char			**linked_list_to_argv(t_list *list)
{
	t_list		*pointer;
	char		**new;
	int			size;

	size = list_size(list);
	new = malloc(sizeof(char **) * size + 1);
	new[size] = NULL;
	size = 0;
	while (list)
	{
		new[size] = list->content;
		size++;
		list = list->next;
	}
	return (new);
}

int		main(int ac, char **av)
{
	t_list	*pointer;
	t_list	*beginning;
	char	**parser;

	/*
	if (ac != 3)
	{
		ft_printf("Nope");
		return (0);
	}
	*/
	// ft_printf("%d", matchparse(av[1], av[2]));
	pointer = get_dir_contents_search("./libft", ac, av);
	beginning = pointer;
	ft_printf("\n");
	while (pointer)
	{
		ft_printf("%s -> ", pointer->content);
		pointer = pointer->next;
	}
	ft_printf("\n");
	parser = linked_list_to_argv(beginning);
	int i = 0;
	while (parser[i])
		ft_printf("%s\n", parser[i++]);
}
