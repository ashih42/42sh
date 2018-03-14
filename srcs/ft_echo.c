#include "ft_42sh.h"

#define INVALID_COLOR -1

static int	insert_color_code(int color)
{
	char	*color_str;

	if (color == INVALID_COLOR)
		return (0);
	color_str = ft_itoa(color);
	if (color_str == 0)
		return (1);
	ft_printf("\e[38;5;%sm", color_str);
	ft_strdel(&color_str);
	return (0);
}

static int	check_flags(char *arg, int *newline, int *color)
{
	if (ft_strequ(arg, "-n"))
	{
		*newline = 0;
		return (1);
	}
	else if (ft_strnequ(arg, "-c", 2))
	{
		if (ft_atoi_check(arg + 2, color) == 0 &&
			0 <= *color && *color <= 255)
			return (1);
	}
	return (0);
}

/*
** ft_echo checks for flags in argv[1], and then argv[2] iff argv[1] is a valid flag
** flag: -n specifies no \n at the end (by default, echo prints \n at the end)
** flag: -cNUM, where NUM indicates text color, valid iff 0 <= NUM <= 255
** See 256 color cheatsheet here: https://jonasjacek.github.io/colors/
*/

void		ft_echo(t_env *e, int argc, char **argv)
{
	int	i;
	int	newline;
	int	need_space;
	int	color;

	(void)e;
	newline = 1;
	color = INVALID_COLOR;
	i = 0;
	if (argc >= 2 && check_flags(argv[1], &newline, &color))
	{
		i++;
		if (argc >= 3 && check_flags(argv[2], &newline, &color))
			i++;
	}
	insert_color_code(color);
	need_space = 0;
	while (++i < argc)
	{
		if (need_space)
			ft_printf(" ");
		ft_printf(argv[i]);
		need_space = 1;
	}
	ft_printf("\033[0m%s", (newline) ? "\n" : "");
}
