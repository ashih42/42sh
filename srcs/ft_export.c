#include "ft_42sh.h"

static int	export_helper(t_env *e, char *str)
{
	char	*name;
	char	*value;

	if (!ft_strchr(str, '='))
	{
		ft_printf("export: lexical error: %s\n", str);
		return (1);
	}
	name = ft_strnew(ft_strchr(str, '=') - str);
	ft_strncpy(name, str, ft_strchr(str, '=') - str);
	value = ft_strchr(str, '=') + 1;
	if (ft_isdigit(name[0]) || !is_valid(name))
	{
		ft_printf("export: not an identifier: %s\n", name);
		ft_strdel(&name);
		return (1);
	}
	set_variable(e, name, value);
	ft_strdel(&name);
	return (0);
}

int			ft_export(t_env *e, int argc, char **argv)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (++i < argc)
		ret |= export_helper(e, argv[i]);
	return (ret);
}

