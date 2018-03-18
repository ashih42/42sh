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

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &e->w);
	num_lines = ((ft_strlen(e->buffer) + (e->promt_len + 2)) / e->w.ws_col);
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

/*
** Super broken function yo...
*/
/*
void	insert_and_update_term(t_env *e, char *new, size_t pos)
{
	size_t	new_s;
	size_t	old_s;
	size_t	i;
	char	*old;

	while (e->cursor++ < e->buffer_end)
		ft_printf("\x1B[C");
	i = 0;
	while (i++ < e->buffer_end)
		ft_printf("\b \b");
	old = get_curr_word(e, pos);
	old_s = ft_strlen(old);
	free(old);
	new_s = ft_strlen(new);
	while (ft_strlen(e->buffer) + new_s > e->buffer_size)
		extend_buffer(e);
	ft_memmove(e->buffer + pos + new_s,
		e->buffer + pos + old_s, e->buffer_end - (pos + old_s));
	ft_memmove(e->buffer + pos, new, new_s);
	e->buffer_end = ft_strlen(e->buffer);
	e->cursor = pos + new_s;
	ft_printf("\n%s\n", e->buffer);
}
*/
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
