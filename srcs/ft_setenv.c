#include "ft_42sh.h"

int			is_valid(char *name)
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

int			ft_setenv(t_env *e, int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("usage: %s var value\n", argv[0]);
		return (1);
	}
	if (ft_isdigit(argv[1][0]) || !is_valid(argv[1]))
	{
		ft_printf("%s: Lexical error\n", argv[0]);
		return (1);
	}
	set_variable(e, argv[1], argv[2]);
	return (0);
}
