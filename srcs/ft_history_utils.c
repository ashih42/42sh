#include "ft_42sh.h"
#define IS_HIDDEN(x) ((x)=='\n'||(x)=='\t'||(x)=='\r'||(x)=='\v'||(x)=='\f')

static size_t	count_rep_chars(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (IS_HIDDEN(*s))
			count++;
		s++;
	}
	return (count);
}

/*
**	show_hide_conv()
**
**	This thing is pretty horrific... -Nick
*/

static char		hidden_convert(char c)
{
	if (c == '\n')
		return ('n');
	else if (c == '\t')
		return ('t');
	else if (c == '\r')
		return ('r');
	else if (c == '\v')
		return ('v');
	else if (c == '\f')
		return ('f');
	else
		return ('\0');
}

/*
**	show_escaped()
**
**	Given some string with an unknown number of '\n' '\r' '\v' '\f' '\t'
**
**	Return a new string where these escaped characters are
**	converted to literal chars that represent them. (i.e. '\n' -> "\\n").
*/

char			*show_escaped(char *s, size_t s_size)
{
	char	*new_start;
	char	*new_s;
	int		rep_cnt;

	rep_cnt = count_rep_chars(s);
	if ((new_s = (char *)malloc((s_size - rep_cnt + 1) * sizeof(char))))
	{
		new_start = new_s;
		while (*s)
		{
			if (IS_HIDDEN(*s))
			{
				*new_s++ = '\\';
				*new_s++ = hidden_convert(*s++);
			}
			else
				*new_s++ = *s++;
		}
		*new_s = '\0';
	}
	return (new_start);
}
