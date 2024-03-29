/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 03:14:39 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 19:14:44 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	We can accomplish reading 1 byte at a time with read() by modifying
**	termios struct and applying the changes with tcsetattr.
**
**	https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
**
**	Turning off ECHO causes the terminal to no longer display a typed character
**	Our 42sh will have to take care of displaying stuff
**
**	Turning off ICANON causes read() to grab input byte-by-byte
**
**	Setting c_cc[VMIN] and c_cc[VTIME] to 1 and 0 respectively will keep
**	read() snappy! See: http://unixwiz.net/techtips/termios-vmin-vtime.html
*/

void	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, orig_termios);
	raw = *orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

void	clear_all_and_update_term(t_env *e, size_t num_nl)
{
	char	*new_buffer;
	size_t	corr_curse_pos;

	corr_curse_pos = e->cursor - 1;
	move_cursor(e, 1, e->buffer_end);
	while (num_nl--)
		ft_putstr("\r\x1B[K\x1B[F");
	if ((new_buffer = ft_strdup(e->buffer)))
	{
		clear_and_update_term(e, new_buffer);
		ft_strdel(&new_buffer);
		if (e->cursor > corr_curse_pos)
			move_cursor(e, 0, (e->cursor - corr_curse_pos));
	}
}

/*
**	clear_and_update_term()
**
**	Used if we need to update the current line of the terminal.
**	(i.e. with ft_history up/down arrows or with tab_autocomplete)
**
**	1) Erase text on current line ('\r' + "\x1B[K")
**	2) Now we can bzero the e->buffer
**	3) cpy the contents of new_str into the e->buffer
**	4) set our cursor position and buffer_end to the size of the new_str
**	5) Reprint our terminal prompt since we erased it in step 1)
**	6) Print the updated e->buffer to show it on screen.
*/

void	clear_and_update_term(t_env *e, char *new_str)
{
	size_t			i;
	size_t			num_lines;
	struct winsize	w;

	if (!new_str)
		return ;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	num_lines = ((ft_strlen(e->buffer) + (e->promt_len + 2)) / w.ws_col);
	while (num_lines--)
	{
		ft_putstr("\r\x1B[K");
		ft_putstr("\x1B[F");
	}
	ft_putstr("\r\x1B[K");
	ft_bzero(e->buffer, e->buffer_end + 1);
	i = ft_strlen(new_str);
	while (i > e->buffer_size)
		extend_buffer(e);
	ft_memmove(e->buffer, new_str, i);
	e->cursor = i;
	e->buffer_end = i;
	e->promt_len = ft_printf("%s %s > ", SPESHELL, get_variable(e, "PWD"));
	ft_printf("%s", e->buffer);
}

size_t	chars_until_newline(t_env *e, size_t cur_pos, int direction)
{
	size_t	start;

	start = cur_pos;
	if (direction)
	{
		while (cur_pos < e->buffer_end && e->buffer[cur_pos] != '\n')
			cur_pos++;
	}
	else
	{
		while (cur_pos > 0 && e->buffer[cur_pos] != '\n')
			cur_pos--;
	}
	return ((start > cur_pos) ? start - cur_pos : cur_pos - start);
}
