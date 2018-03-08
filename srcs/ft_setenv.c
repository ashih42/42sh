#include "ft_42sh.h"

void		ft_setenv(t_env *e, int argc, char **argv)
{
	if (argc >= 3)
	{
		set_variable(e, argv[1], argv[2]);
	}

}
