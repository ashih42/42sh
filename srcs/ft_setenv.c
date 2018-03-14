#include "ft_42sh.h"

static int	is_valid(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
			return (0);
	}
	return (1);
}

/*
**	int		ft_setenv(t_env *e, int argc, char **argv)
**	{
**		if (argc != 3)
**			return (ft_puterror("usage: setenv var value", 0, 1));
**		if (ft_isdigit(argv[1][0]))
**			return (ft_puterror("var name must not start with digit", 0, 1));
**		if (!is_valid(argv[1]))
**			return (ft_puterror("var name must contain only alphabet, digit, and _ characters", 0, 1));
**		set_variable(e, argv[1], argv[2]);
**		return (0);
**	}
*/

int		ft_setenv(t_env *e, int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("usage: setenv var value\n");
		return (1);
	}
	if (ft_isdigit(argv[1][0]) || !is_valid(argv[1]))
	{
		ft_printf("setenv: Lexical error\n");
		return (1);
	}
	set_variable(e, argv[1], argv[2]);
	return (0);
}
