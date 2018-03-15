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

#include <sys/ioctl.h>
int 	get_term_width(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

/*
**	clear_and_update_term()
**
**	Used if we need to update the current line of the terminal.
**	(i.e. with ft_history up/down arrows or with tab_autocomplete)
**
**	1) If the user's cursor is not at the end of the curr text, move it there
**	2) Erase text on screen (amount of text is specified by e->buff_end)
**	3) Now we can bzero the e->buffer
**	4) cpy the contents of new_str into the e->buffer
**	5) set our cursor position and buffer_end to the size of the new_str
**	6) Print the updated e->buffer to show it on screen.
*/

void	clear_and_update_term(t_env *e, char *new_str)
{
	size_t	i;

	while (e->cursor++ < e->buffer_end)
		ft_printf("\x1B[C");

	i = 0;
	while (i++ < e->buffer_end)
		ft_printf("\b \b");
	ft_bzero(e->buffer, e->buffer_end + 1);
	i = ft_strlen(new_str);
	ft_memmove(e->buffer, new_str, i);
	e->cursor = i;
	e->buffer_end = i;

	if (((int)(ft_strlen(get_variable(e, "PWD"))
		 + ft_strlen(e->buffer) + 8)) >
		get_term_width())
		ft_printf("\x1B[C");

	ft_printf("%s", e->buffer);
}

/*
**	move_cursor()
**
**	Moves our terminal cursor:
**	RIGHT (direction = 1)
**	LEFT (direction = 0)
**
**	The cursor will be moved in 'direction' a total of 'n_times' except if
**	the cursor hits the start or end position of the e->buffer.
*/

void	move_cursor(t_env *e, int direction, size_t n_times)
{
	while (n_times--)
	{
		if (direction && e->cursor < e->buffer_end)
		{
			e->cursor++;
			ft_putstr("\x1B[C");
		}
		else if (!direction && e->cursor > e->buffer_lock)
		{
			e->cursor--;
			ft_putstr("\x1B[D");
		}
	}
}
