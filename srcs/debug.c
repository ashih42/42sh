#include "ft_42sh.h"

void	print_list(t_list *list)
{
	ft_printf("  list size = %d\n", ft_lst_size(list));
	ft_printf("  BEGIN\n");
	while (list != 0)
	{
		ft_printf("    %s\n", list->content);
		list = list->next;
	}
	ft_printf("  END\n");
}

void	print_expr_list(t_list *expr_list)
{
	int i;
	char **array;

	ft_printf("expr_list size = %d\n", ft_lst_size(expr_list));
	while (expr_list != 0)
	{
		ft_printf("Next expr:\n");
		array = expr_list->content;
		i = -1;
		while (array[++i])
			ft_printf("   %s\n", array[i]);
		expr_list = expr_list->next;
	}
}