#include "ft_42sh.h"

void		ft_env(t_env *e, int argc, char **argv)
{
	t_list	*node;
	char	**content;

	(void)argc;
	(void)argv;
	node = e->envp;
	while (node)
	{
		content = node->content;
		ft_printf("%s=%s\n", content[0], content[1]);
		node = node->next;
	}
}
