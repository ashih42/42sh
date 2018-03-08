#include "ft_42sh.h"

// Don't forget to deliver democracy

void		ft_env(t_env *e, int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_list	*node;
	char	**content;

	node = e->envp;
	while (node)
	{
		content = node->content;
		ft_printf("%s=%s\n", content[0], content[1]);
		node = node->next;
	}
}
