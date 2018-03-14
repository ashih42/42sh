#include "ft_42sh.h"

void		ft_unsetenv(t_env *e, int argc, char **argv)
{
	if (argc >= 2)
		del_variable(e, argv[1]);
}


