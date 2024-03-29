/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 18:26:42 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:23:03 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	sh_parse()
**
**	This function will take the input read in via sh_listen() and parse it for
**	redirections, escaped characters, etc.
*/

static int		is_delim(char *s)
{
	static char	*delim_table[] = {";", "||", "&&", "|", ">>", ">", "<", 0};
	int			i;

	i = 0;
	while (delim_table[i])
	{
		if (ft_strnequ(s, delim_table[i],
			ft_strlen(delim_table[i])))
			return (ft_strlen(delim_table[i]));
		i++;
	}
	return (0);
}

static void		add_terms_helper(char *s, t_add_terms *at)
{
	while (s[at->i] && (at->quote || !(at->inc = is_delim(s + at->i))))
	{
		if (s[at->i] == '\\')
			at->i++;
		else if (!at->quote && (s[at->i] == '\'' || s[at->i] == '\"'))
			at->quote = s[at->i];
		else if (at->quote && s[at->i] == at->quote)
			at->quote = 0;
		if (!s[at->i])
			break ;
		at->i++;
	}
}

static void		add_terms(char *s, t_list **list)
{
	t_add_terms	at;

	ft_bzero(&at, sizeof(t_add_terms));
	while (1)
	{
		at.head = at.i;
		add_terms_helper(s, &at);
		if (at.i > at.head)
		{
			at.word = ft_strnew(at.i - at.head);
			ft_strncpy(at.word, s + at.head, at.i - at.head);
			ft_lst_add_last(list, ft_lst_new_ref(at.word, sizeof(char *)));
		}
		if (s[at.i] == '\0')
			return ;
		at.word = ft_strnew(at.inc);
		ft_strncpy(at.word, s + at.i, at.inc);
		ft_lst_add_last(list, ft_lst_new_ref(at.word, sizeof(char *)));
		at.i += at.inc;
	}
}

/*
** Explode a string and build a char ** array from the pieces.
** e.g. "ls|cat>>txt" becomes "ls", "|", "cat", ">>", "txt"
*/

static char		**str_explode2(char *s)
{
	char	**result;
	t_list	*list;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	list = 0;
	add_terms(s, &list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
	return (result);
}

char			***sh_parse(t_env *e)
{
	char	**cmds;
	char	***result;
	size_t	i;
	size_t	j;

	result = NULL;
	cmds = str_explode2(e->buffer);
	if (cmds)
	{
		if ((result = ft_memalloc(
			(ft_char_array_length(cmds) + 1) * sizeof(char ***))))
		{
			i = -1;
			j = 0;
			while (cmds[++i])
				if ((result[j] = split_argv(cmds[i], WHITESPACE)))
					j++;
			if (!j)
				ft_memdel((void **)&result);
		}
		ft_char_array_del(cmds);
	}
	return (result);
}
