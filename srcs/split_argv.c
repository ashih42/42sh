/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 19:25:41 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:20:51 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	is_ws(char c, char *ws)
{
	int i;

	i = 0;
	while (ws[i])
	{
		if (ws[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	add_terms_helper(char *ws, t_add_terms *at)
{
	while (is_ws(at->work_buf[at->i], ws))
		at->i++;
	at->head = at->i--;
	while (at->work_buf[++(at->i)])
	{
		if ((!at->quote && (at->work_buf[at->i] == '\"' ||
			at->work_buf[at->i] == '\'')))
			at->quote = at->work_buf[at->i];
		else if (at->work_buf[at->i] == at->quote)
			at->quote = 0;
		else if (at->work_buf[at->i] == '\\' && (!at->quote ||
			at->work_buf[at->i + 1] == '\'' || at->work_buf[at->i + 1] == '\"'
			|| at->work_buf[at->i + 1] == '$'))
		{
			if (!at->work_buf[++(at->i)])
				break ;
		}
		else if (!at->quote && is_ws(at->work_buf[at->i], ws))
			break ;
	}
}

static void	add_terms(char const *s, t_list **list, char *ws)
{
	t_add_terms	at;
	t_list		*glob;

	ft_bzero(&at, sizeof(t_add_terms));
	at.work_buf = ft_strdup(s);
	while (at.work_buf[at.i])
	{
		add_terms_helper(ws, &at);
		if (at.i <= at.head)
			continue ;
		at.word = ft_strnew(at.i - at.head);
		ft_strncpy(at.word, at.work_buf + at.head, at.i - at.head);
		if (should_glob(at.word))
		{
			if ((glob = ft_glob(truncate_wildcards(at.word))))
				ft_lst_add_last(list, glob);
			else
				ft_printf("42sh: no matches found: %s\n", at.word);
			free(at.word);
		}
		else
			ft_lst_add_last(list, ft_lst_new_ref(at.word, sizeof(char *)));
	}
	free(at.work_buf);
}

char		**split_argv(char const *s, char *ws)
{
	char	**result;
	t_list	*list;
	size_t	size;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	list = NULL;
	add_terms(s, &list, ws);
	if (list == NULL)
		return (NULL);
	size = ft_lst_size(list);
	result = list_to_array(list);
	ft_lstdel(&list, (void (*)(void *, size_t))free);
	strip_argv(result);
	return (result);
}
