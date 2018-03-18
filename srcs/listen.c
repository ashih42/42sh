#include "ft_42sh.h"

static void	lstn_loop(t_env *e, char *c, size_t i)
{
	int	br;

	while ((br = read(STDIN_FILENO, c, 1)) > 0)
	{
		if (*c == '\n' && submit_attempt(e))
			break ;
		if (e->buffer_end == e->buffer_size && !extend_buffer(e))
			return ;
		if (char_specs(e, *c))
			continue ;
		ft_memmove(e->buffer + e->cursor + 1,
					e->buffer + e->cursor, e->buffer_end++ - e->cursor);
		e->buffer[e->buffer_end] = '\0';
		i = e->cursor++;
		e->buffer[i] = *c;
		if (*c == '\n')
			continue ;
		ft_printf("%s", e->buffer + (e->cursor - 1));
		e->cursor = e->buffer_end;
		while (++i < e->buffer_end)
			move_cursor(e, 0, 1);
	}
	(br <= 0) ? ft_strdel(&(e->buffer)) : (void)0;
	ft_putchar('\n');
}

/*
**	sh_listen()
**
**	This function should implement listening on stdin. Will need to read
**	one char at a time so that backspaces and tabs will be supported!!!
**
**	Because the input is of an unspecified length, we will either need to
**	realloc when we are about to go over our allocation limit.
*/

void		sh_listen(t_env *e)
{
	struct termios	orig_termios;
	char			c;

	ft_bzero(e->buffer, e->buffer_size + 1);
	e->cursor = 0;
	e->buffer_lock = 0;
	e->buffer_end = 0;
	e->promt_len = ft_printf("%s %s > ", SPESHELL, get_variable(e, "PWD"));
	enable_raw_mode(&orig_termios);
	lstn_loop(e, &c, 0);
	disable_raw_mode(&orig_termios);
}
