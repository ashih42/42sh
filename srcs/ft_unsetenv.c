#include "ft_42sh.h"

// should this REMOVE or SET TO EMPTY STRING ??

void		ft_unsetenv(t_env *e, int argc, char **argv)
{
	if (argc >= 2)
	{
		del_variable(e, argv[1]);
//		if (get_variable(e, argv[1]))
//			set_variable(e, argv[1], "");
	}

}


