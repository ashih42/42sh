#include "ft_42sh.h"

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
		e->buffer_size += BUFFER_SIZE;
		return (1);
	}
	return (0);
}

/*
**	handle_esc_seq()
**
**	After getting an escape byte '\027' ('\x1B') need to read more bytes to
**	see what the full escape sequence is...
**
**	'\027[D'	LEFT
**	'\027[C'	RIGHT
**	'\027[A'	UP
**	'\027[B'	DOWN
**	'\027[H'	HOME key - Brings cursor to position 0
**	'\027[F'	END key - Brings cursor to e->buffer_end
*/

int		handle_esc_seq(t_env *e, char c)
{
	read(STDIN_FILENO, &c, 1);
	if (c == '[')
	{
		read(STDIN_FILENO, &c, 1);
		if (c == 'D')
			move_cursor(e, 0, 1);
		else if (c == 'C')
			move_cursor(e, 1, 1);
		else if (c == 'A')
			get_cmd_history(e, 0);
		else if (c == 'B')
			get_cmd_history(e, 1);
		else if (c == 'H')
			move_cursor(e, 0, e->cursor);
		else if (c == 'F')
			move_cursor(e, 1, e->buffer_end - e->cursor);
	}
	return (1);
}

/*
**	Handles special characters like TAB, LEFT, RIGHT, and DEL
**
**	127 ('\b'):		BACKSPACE
**	027 ('\x1B'):	ESC
*/

int		char_specs(t_env *e, char c)
{
	size_t	i;

	if (c == 127 || c == '\b')
	{
		if (e->cursor > e->buffer_lock)
		{
			ft_memmove(e->buffer + e->cursor - 1,
						e->buffer + e->cursor, e->buffer_end - e->cursor);
			i = --e->buffer_end;
			e->buffer[i] = '\0';
			ft_printf("\b%s \b", e->buffer + --e->cursor);
			while (i-- > e->cursor)
				ft_putchar('\b');
		}
		return (1);
	}
	if (c == '\t')
		return (tab_autocomplete(e));
	if (c == '\x1B')
		return (handle_esc_seq(e, c));
	return (0);
}

int		submit_attempt(t_env *e)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (e->buffer[i])
	{
		if (!quote && (e->buffer[i] == '\'' || e->buffer[i] == '\"'))
			quote = e->buffer[i];
		else if (e->buffer[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
	{
		if (quote == '\'')
			ft_printf("\nquote> ");
		if (quote == '\"')
			ft_printf("\ndquote> ");
		e->buffer_lock = e->buffer_end + 1;
		return (0);
	}
	return (1);
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
	e->buffer_lock = 0;
	e->buffer_end = 0;
	ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	enable_raw_mode(&orig_termios);
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c != '\t')
			e->reset_tab_auto = 1;
		if (c == '\n' && submit_attempt(e))
			break ;
		if (e->buffer_end == e->buffer_size && !extend_buffer(e))
			return ;
		if (char_specs(e, c))
			continue ;
		ft_memmove(e->buffer + e->cursor + 1,
					e->buffer + e->cursor, e->buffer_end++ - e->cursor);
		i = e->cursor++;
		e->buffer[i] = c;
		if (c == '\n')
			continue ;
		ft_printf("%s", e->buffer + (e->cursor - 1));
		while (++i < e->buffer_end)
			ft_putchar('\b');
	}
	ft_putchar('\n');
	disable_raw_mode(&orig_termios);
}
