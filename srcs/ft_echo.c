#include "ft_42sh.h"

// flags: -n (removes \n at end)

// RIGHT NOW THIS DOESN'T WORK IN GENERAL IF ARGS
// have any quotes,
// have an opening quote only -> need shell to ask for more args

/* ANDY NO
int		print_term(t_env *e, char *str)
{
	char	*value;

	if (str[0] == '$')
	{
		value = get_variable(e, str + 1);
		if (value)
		
			ft_printf(value);
		else
			return (0);
	}
	else
		ft_printf(str);
	return (1);
}
*/

void		ft_echo(t_env *e, int argc, char **argv)
{
	int i;
	int newline;
	int need_space;

	i = (argc > 1 && ft_strnequ(argv[1], "-n", 2)) ? 1 : 0;
	newline = !i;
	need_space = 0;
	while (++i < argc)
	{
		if (need_space)
			ft_printf(" ");
		ft_printf(argv[i]);
		need_space = 1;
	}
	ft_printf((newline) ? "\n" : "");
}

