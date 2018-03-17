#include "ft_42sh.h"

int			ft_unset(t_env *e, int argc, char **argv)
{
	int		i;

	i = 0;
	if (e->envp)
	{
		while (++i < argc)
			del_variable(e, argv[i]);
	}
	return (0);
}
