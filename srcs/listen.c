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
*/

void	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, orig_termios);
	raw = *orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

/*
**	Extends e->buffer when there's no more space.
*/

int		extend_buffer(t_env *e)
{
	char	*new_buffer;

	if ((new_buffer = ft_strnew(e->buffer_size + BUFFER_SIZE)))
	{
		ft_memcpy(new_buffer, e->buffer, e->buffer_size);
		free(e->buffer);
		e->buffer = new_buffer;
		return (1);
	}
	return (0);
}

/*
**	Handles special characters like TAB, LEFT, RIGHT, and DEL
*/

//NEEDS SOME MAJOR NORM LOL

int		char_specs(t_env *e, char c)
{
	size_t	i;

	if (c == 127 || c == '\b') //BACKSPACE
	{
		if (e->cursor)
		{
			ft_memmove(e->buffer + e->cursor - 1, e->buffer + e->cursor, e->buffer_end - e->cursor);
			e->buffer[(i = --e->buffer_end)] = '\0';
			ft_printf("\b%s \b", e->buffer + --e->cursor);
			while (i-- > e->cursor)
				ft_putchar('\b');
		}
		return (1);
	}
	if (c == '\t') //TAB
	{
		//lol no thanks
		return (1);
	}
	if (c == '\x1B') //ESC
	{
		read(STDIN_FILENO, &c, 1);
		if (c == '[')
		{
			read(STDIN_FILENO, &c, 1);
			if (c == 'D' && e->cursor) //LEFT
			{
				e->cursor--;
				ft_putstr("\x1B[D");
			}
			if (c == 'C' && e->cursor < e->buffer_end) //RIGHT
			{
				e->cursor++;
				ft_putstr("\x1B[C");
			}
		}
		return (1);
	}
	return (0);
}

/*
**	sh_listen()
**
**	This function should implement listening on stdin. Will need to read
**	one char at a time so that backspaces and tabs will be supported!!!
**
**	Because the input is of an unspecified length, we will either need to
**	realloc when we are about to go over our allocation limit or use some
**	sort of linked list implementation...
*/

void	sh_listen(t_env *e)
{
	struct termios	orig_termios;
	char			c;
	size_t			i;

	ft_bzero(e->buffer, e->buffer_size + 1);
	e->cursor = 0;
	e->buffer_end = 0;
	ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	enable_raw_mode(&orig_termios);
	while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n')
	{
		if (char_specs(e, c))
			continue ;
		if (e->buffer_end == e->buffer_size)
			extend_buffer(e);
		ft_memmove(e->buffer + e->cursor + 1, e->buffer + e->cursor, e->buffer_end++ - e->cursor);
		e->buffer[(i = e->cursor)] = c;
		ft_printf("%s", e->buffer + e->cursor++);
		while (++i < e->buffer_end)
			ft_putchar('\b');
	}
	ft_putchar('\n');
	disable_raw_mode(&orig_termios);
}
