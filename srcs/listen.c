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

void enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, orig_termios);
	raw = *orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
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

	ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	//keeping this for now if people want to test other parts of program
	//del_and_gnl(STDIN_FILENO, &(e->buffer)); //TODO: read one character at a time to detect tabs :sob:
	
	//TODO: Need a way to recognize escaped multibyte inputs (i.e. ^[[A)
	//		Need a way to store read in bytes into a buffer that can expand
	//		Need a way to edit bytes in buffer when getting 'backspace' input
	//		Need a way to edit bytes in buffer if cursor is moved left or right
	//		And more!!
	enable_raw_mode(&orig_termios);
	while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n')
	{
		if (ft_isprint(c))
			ft_printf("%c", c);
	}
	disable_raw_mode(&orig_termios);

}
