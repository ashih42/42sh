/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:49:13 by apuel             #+#    #+#             */
/*   Updated: 2018/03/11 23:16:58 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int is_delim(char *s)
{
	static char *delim_table[] = {";", "||", "&&", "|", 0};
	int i;

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

static void		add_terms(char *s, t_list **list)
{
	int head;
	int i;
	char *word;
	int inc;
	char quote;

	i = 0;
	quote = 0;
	while (1)
	{
		head = i;
		while (s[i] && (quote || !(inc = is_delim(s + i))))
		{
			if (s[i] == '\\')
				i++;
			else if (!quote && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (quote && s[i] == quote)
				quote = 0;
			if (!s[i])
				break ;
			i++;
		}
		if (i > head)
		{
			word = ft_strnew(i - head);
			ft_strncpy(word, s + head, i - head);
			ft_lst_add_last(list, ft_lst_new_ref(word, sizeof(char *)));
		}
		if (s[i] == '\0')
			return ;
		word = ft_strnew(inc);
		ft_strncpy(word, s + i, inc);
		ft_lst_add_last(list, ft_lst_new_ref(word, sizeof(char *)));
		i += inc;
	}
}

/*
** This amazing function makes a string explode and adds the pieces to end of list.
** e.g. "ls|cat>>txt" becomes "ls" -> "|" -> "cat" -> ">>" -> "txt"
*/

static char		**str_explode2(char *s)
{
	char	**result;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	t_list *list = 0;
	add_terms(s, &list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
	return (result);
}

char	***ft_3d_parser(char *input)
{
	char	**cmds;
	char	***result;
	size_t	i;

	cmds = str_explode2(input);
	result = ft_memalloc((ft_char_array_length(cmds) + 1) * sizeof(char ***));
	i = -1;
	while (cmds[++i])
		result[i] = split_argv(cmds[i], WHITESPACE);
	ft_char_array_del(cmds);
	return (result);
}
