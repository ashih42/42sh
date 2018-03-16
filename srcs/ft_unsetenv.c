#include "ft_42sh.h"

int			ft_unsetenv(t_env *e, int argc, char **argv)
{
	if (argc >= 2 && e->envp)
		del_variable(e, argv[1]);
	return (0);
}
