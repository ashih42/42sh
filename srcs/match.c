#include "ft_42sh.h"

static int		dequeue(t_list **stack, char c)
{
	char		*top;

	if (!(c == '}' || c == ']'))
		return (0);
	if (ft_lst_size(*stack) == 0)
		return (-1);
	top = ft_lst_remove_first(stack);
	if ((c == '}' && ft_strequ(top, "{")) ||
		(c == ']' && ft_strequ(top, "[")))
		return (0);
	else
		return (-1);
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

int				valid_brackets(char *s)
{
	t_list		*stack;
	int			ret;
	size_t		i;

	stack = NULL;
	ret = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '{' && (i == 0 || s[i - 1] != '\\'))
			ft_lstadd(&stack, ft_lst_new_ref("{", sizeof(char *)));
		else if (s[i] == '[' && (i == 0 || s[i - 1] != '\\'))
			ft_lstadd(&stack, ft_lst_new_ref("[", sizeof(char *)));
		if ((i == 0 || s[i - 1] != '\\') &&
			(ret = dequeue(&stack, s[i])) < 0)
			break ;
		i++;
	}
	ft_lstdel(&stack, NULL);
	return (ret);
}

int				should_glob(char *s2)
{
	size_t	i;
	int		expr;

	expr = 0;
	i = -1;
	while (s2[++i])
	{
		if ((s2[i] == '\'' || s2[i] == '\"') && (i == 0 || s2[i - 1] != '\\'))
			return (0);
		if ((s2[i] == '*' || s2[i] == '[' || s2[i] == '?' || s2[i] == '{') &&
			(i == 0 || s2[i - 1] != '\\'))
			expr = 1;
	}
	return (expr);
}

int				match(char *s1, char *s2)
{
	size_t	cnt;

	while (1)
	{
		cnt = 0;
		if (*s2 == '\\')
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
