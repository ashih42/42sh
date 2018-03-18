/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 05:03:27 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:20:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	get_curr_word()
**
**	This function will get the first non-space character sequence that occurs
**	before the specified cursor_pos.
**
**	If the cursor_pos is in the middle of a word, then the function will return
**	the entire word.
**
**	Spaces are defined as: ' ', '\t', '\n', '\r', '\f', or '\v'
*/

static char		*get_curr_word(t_env *e)
{
	char	*curr_word;
	size_t	wend_pos;
	size_t	word_len;

	curr_word = NULL;
	while (e->buffer[e->cursor] && (!ft_is_space(e->buffer[e->cursor]) ||
		(e->cursor > 0 && e->buffer[e->cursor - 1] == '\\')))
		e->cursor++;
	wend_pos = e->cursor;
	while (e->cursor > 0 && (!ft_is_space(e->buffer[e->cursor - 1]) ||
		(e->cursor > 1 && e->buffer[e->cursor - 2] == '\\')))
		e->cursor--;
	word_len = wend_pos - e->cursor;
	if (word_len && (curr_word = ft_strnew(word_len + 1)))
		ft_strncpy(curr_word, e->buffer + e->cursor, word_len);
	return (curr_word);
}

static void		get_word_path(t_env *e, char **word, char **path)
{
	int		i;

	*path = 0;
	if (!*word || !ft_strchr(*word, '/'))
		return ;
	*path = *word;
	i = -1;
	while (ft_strchr(*path + ++i, '/'))
		e->cursor++;
	*word = ft_strdup(*path + i);
	(*path)[i] = '\0';
}

static int		is_first_word(t_env *e)
{
	size_t	curs;
	size_t	chkpnt;

	curs = e->cursor;
	while (curs > 0 && (!ft_is_space(e->buffer[curs - 1]) ||
		(curs > 1 && e->buffer[curs - 2] == '\\')))
		curs--;
	chkpnt = curs;
	while (curs > 0 && ft_is_space(e->buffer[curs - 1]) &&
		(curs <= 1 || e->buffer[curs - 2] != '\\'))
		curs--;
	if (curs == 0 && (e->cursor == 0 || chkpnt == 0 ||
			ft_is_space(e->buffer[0])))
		return (1);
	else
		return (0);
}

int				tab_autocomplete(t_env *e)
{
	char	*word;
	char	*path;
	size_t	temp;
	int		result;

	temp = e->cursor;
	word = get_curr_word(e);
	get_word_path(e, &word, &path);
	if (is_first_word(e))
		result = ac_first_word(e, word, path);
	else
		result = ac_not_first_word(e, word, path);
	if (!result)
		e->cursor = temp;
	ft_strdel(&word);
	ft_strdel(&path);
	return (1);
}
