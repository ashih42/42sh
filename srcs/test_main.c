#include <ft_42sh.h>

int matchparse(char *s1, char *s2);

int		main(int ac, char **av)
{
	t_list	*pointer;

	/*
	if (ac != 3)
	{
		ft_printf("Nope");
		return (0);
	}
	*/
	// ft_printf("%d", matchparse(av[1], av[2]));
	pointer = get_dir_contents_search("./", 0, ac, av);
	ft_printf("\n");
	while (pointer)
	{
		ft_printf("%s -> ", pointer->content);
		pointer = pointer->next;
	}
	ft_printf("\n");
}
