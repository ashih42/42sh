#include "ft_42sh.h"

static int	dequeue(t_list **stack, char c)
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

int			valid_brackets(char *s)
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
	if (stack)
		ret = -1;
	ft_lstdel(&stack, NULL);
	return (ret);
}

int			should_glob(char *s2)
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

static char	*expand_filename(char *s)
{
	size_t	i;
	size_t	diff;
	char	*new;
	size_t	j;

	diff = 0;
	i = -1;
	while (s[++i])
		if ((s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
			diff++;
	new = NULL;
	if (diff && (new = ft_strnew(i + diff)))
	{
		i = -1;
		j = 0;
		while (s[++i])
		{
			if ((s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
				new[j++] = '\\';
			new[j++] = s[i];
		}
	}
	return (new);
}

t_list		*expand_filenames(t_list *files)
{
	t_list	*temp;
	char	*orig;

	temp = files;
	while (temp)
	{
		orig = temp->content;
		if ((temp->content = expand_filename(orig)))
			free(orig);
		else
			temp->content = orig;
		temp = temp->next;
	}
	return (files);
}
