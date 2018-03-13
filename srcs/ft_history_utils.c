#include "ft_42sh.h"
#define IS_HIDDEN(x) ((x)=='\n'||(x)=='\t'||(x)=='\r'||(x)=='\v'||(x)=='\f')
#define IS_SHOWN(y) ((y)=='n'||(y)=='t'||(y)=='r'||(y)=='v'||(y)=='f')

static size_t	count_rep_chars(char *s, int mode)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (mode == 0 && IS_HIDDEN(*s))
			count++;
		else if (mode == 1 && (*s == '\\' && *(s + 1) && IS_SHOWN(*(s + 1))))
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

static char		show_hide_convert(char c, int mode)
{
	if (mode && c == 'n')
		return ('\n');
	else if (mode && c == 't')
		return ('\t');
	else if (mode && c == 'r')
		return ('\r');
	else if (mode && c == 'v')
		return ('\v');
	else if (mode && c == 'f')
		return ('\f');
	else if (!mode && c == '\n')
		return ('n');
	else if (!mode && c == '\t')
		return ('t');
	else if (!mode && c == '\r')
		return ('r');
	else if (!mode && c == '\v')
		return ('v');
	else if (!mode && c == '\f')
		return ('f');
	else
		return ('\0');
}

/*
**	show_hide_escape()
**
**	Given some string with an unknown number of '\n' '\r' '\v' '\f' '\t' or
**	"\\n" "\\r" "\\v" "\\f" "\\t"
**
**	If (mode = 0) return a new string where these escaped characters are
**	converted to literal chars that represent them. (i.e. '\n' -> "\\n").
**
**	If (mode = 1) return a new string where literal chars are replaced with
**	the single-byte version. (i.e. "\\r" -> '\r')
*/

//norm me please :O

char			*show_hide_escape(char *s, size_t s_size, int mode)
{
	char	*new_start;
	char	*new_s;
	int		new_size;
	int		rep_cnt;

	rep_cnt = count_rep_chars(s, mode);
	new_size = (mode) ? s_size + rep_cnt : s_size - rep_cnt;
	if ((new_s = (char *)malloc((new_size + 1) * sizeof(char))))
	{
		new_start = new_s;
		while (*s)
		{
			if (!mode && IS_HIDDEN(*s))
			{
				*new_s++ = '\\';
				*new_s++ = show_hide_convert(*s++, mode);
			}
			else if (mode && *s == '\\' && *(s + 1) && IS_SHOWN(*(s + 1)))
			{
				s++;
				*new_s++ = show_hide_convert(*s++, mode);
			}
			else
				*new_s++ = *s++;
		}
		*new_s = '\0';
	}
	return (new_start);
}
