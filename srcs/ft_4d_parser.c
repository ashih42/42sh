/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:49:13 by apuel             #+#    #+#             */
/*   Updated: 2018/03/11 12:26:06 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	}
*/

static int is_delim(char *s)
{
	static char *delim_table[] = {"||", "&&", "|", 0};
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
	char *d;
	int inc;

	i = 0;
	while (1)
	{
		head = i;
		while (!(inc = is_delim(s + i)) && s[i] != '\0')
			i++;
		if (i > head)
		{
			word = ft_strnew(i - head);
			ft_strncpy(word, s + head, i - head);
			ft_lst_add_last(list, ft_lst_new_ref(word, sizeof(char *)));
		}
		if (s[i] == '\0')
			return ;
		d = ft_strnew(inc);
		ft_strncpy(d, s + i, inc);
		ft_lst_add_last(list, ft_lst_new_ref(d, sizeof(char *)));
		i += inc;
	}
}

/*
** This amazing function makes a string explode and adds the pieces to end of list.
** e.g. "ls|cat>>txt" becomes "ls" -> "|" -> "cat" -> ">>" -> "txt"
*/

static char		**str_explode2(char *s)
{
	if (s == NULL || s[0] == '\0')
		return (NULL);
	t_list *list = 0;
	add_terms(s, &list);
	return (list_to_array(list));
}

char	****ft_4d_parser(char *input)
{
	char	**groups;
	char	**cmds;
	char	****result;
	size_t	i;
	size_t	j;

	groups = ft_strsplit(input, ';');
	result = ft_memalloc((ft_char_array_length(groups) + 1) * sizeof(char ****));
	i = -1;
	while (groups[++i])
	{
//		cmds = //a form of ft_strsplit that splits between '|' and '&&' (shouldn't remove '|', leave it at the end of the left string)
		cmds = str_explode2(groups[i]);		// e.g. commands: (ls -a), (&&), (echo hello)
		result[i] = ft_memalloc((ft_char_array_length(cmds) + 1) * sizeof(char ***));
		j = -1;
		while (cmds[++j])
			result[i][j] = split_argv(cmds[j], WHITESPACE);
		ft_char_array_del(cmds);
	}
	ft_char_array_del(groups);
	return (result);
}
