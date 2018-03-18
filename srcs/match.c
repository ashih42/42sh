#include "ft_42sh.h"

char			*truncate_wildcards(char *query)
{
	size_t	i;

	i = 0;
	while (query[i])
	{
		if (query[i] == '*' && (i == 0 || query[i - 1] != '\\'))
		{
			if (i == 0 || query[i - 1] != '*')
				i++;
			else
				ft_memmove(query + i, query + i + 1, ft_strlen(query + i));
		}
		else
			i++;
	}
	return (query);
}

static size_t	chk_glob_brckts(char c1, char *s2)
{
	size_t	i;
	int		match;

	match = 0;
	if (s2[i = 0] == '[')
		while (s2[++i] && s2[i] != ']')
		{
			if (s2[i] == '\\' && !s2[++i])
				break ;
			if (s2[i] == '-' && (s2[i - 1] != '\\' ||
				(i > 1 && s2[i - 2] == '\\')))
			{
				if (s2[i + 1] != '\\')
					match |= (c1 > s2[i - 1] && c1 < s2[i + 1]);
				else
					match |= (c1 > s2[i - 1] && c1 < s2[i + 2]);
			}
			else if (c1 == s2[i])
				match = 1;
		}
	if (match)
		return (i);
	return (0);
}

int				match(char *s1, char *s2)
{
	size_t	cnt;

	while (1)
	{
		if (!(cnt = 0) && *s2 == '\\')
		{
			if (*s1 != *(++s2))
				return (0);
			(*s1++ && *s2) ? s2++ : s1--;
		}
		if (*s1 == '\0' && *s2 == '\0')
			return (1);
		if ((*s1 == *s2 && *s1 != '[' && *s1 != '{' && *s1 != '*') ||
			*s2 == '?' || (*s2 == '[' && (cnt = chk_glob_brckts(*s1, s2))))
		{
			s2 += cnt + 1;
			s1++;
		}
		else if (*s1 == '\0' && *s2 == '*')
			s2++;
		else if (*s1 == '\0' || *s2 == '\0' || *s2 != '*')
			return (0);
		else if (match(s1++, s2 + 1))
			return (1);
	}
}
