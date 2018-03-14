#include <ft_42sh.h>

char			**linked_list_to_argv(t_list *list);

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
