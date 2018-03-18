#include "ft_42sh.h"

/*
**	Extends e->buffer when there's no more space.
*/

int			extend_buffer(t_env *e)
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

int			handle_esc_seq(t_env *e, char c)
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
			move_cursor(e, 2, 1);
		else if (c == 'B')
			move_cursor(e, 3, 1);
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

int			char_specs(t_env *e, char c)
{
	size_t	i;

	if (c != '\t')
		e->need_files_list = 1;
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
	if (ft_isprint(c) || (c == '\n'))
		return (0);
	if (c == '\x04' && !(e->buffer_end))
		close(STDIN_FILENO);
	return (1);
}

int			submit_attempt(t_env *e)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (e->buffer[i])
	{
		if (!quote && (e->buffer[i] == '\'' || e->buffer[i] == '\"') &&
			(i == 0 || e->buffer[i - 1] != '\\'))
			quote = e->buffer[i];
		else if (e->buffer[i] == quote && e->buffer[i - 1] != '\\')
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
