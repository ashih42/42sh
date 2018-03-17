#include "ft_42sh.h"

/*
**	move_left()
**
**	Function to move our cursor left. Can also handle 'leftward' traversal of
**	multiline content.
*/

static void	move_left(t_env *e, size_t n_fl_chars)
{
	size_t	n_chars;
	int		i;

	i = -1;
	if (e->buffer[--e->cursor] == '\n')
	{
		ft_putstr("\x1B[F");
		n_chars = chars_until_newline(e, e->cursor - 1, 0) + 1;
		while (n_chars--)
			ft_putstr("\x1B[C");
		if (e->cursor <= n_fl_chars)
		{
			while (++i < e->promt_len + 3)
				ft_putstr("\x1B[C");
		}
	}
	ft_putstr("\x1B[D");
}

/*
**	move_right()
**
**	Function to move our cursor right. Can also handle 'rightward' traversal of
**	multiline content.
*/

static void	move_right(t_env *e, size_t n_fl_chars)
{
	size_t	n_chars;
	int		i;

	i = -1;
	if (e->buffer[e->cursor] == '\n')
	{
		if (e->cursor > n_fl_chars + 3)
		{
			while (++i < e->promt_len)
				ft_putstr("\x1B[D");
		}
		ft_putstr("\x1B[E");
		n_chars = chars_until_newline(e, e->cursor + 1, 1) + 2;
		while (n_chars--)
			ft_putstr("\x1B[D");
	}
	else
		ft_putstr("\x1B[C");
	e->cursor++;
}

static void	move_up(t_env *e)
{
	get_cmd_history(e, 0);
}

static void	move_down(t_env *e)
{
	get_cmd_history(e, 1);
}

/*
**	move_cursor()
**
**	Moves our terminal cursor:
**	LEFT	(direction = 0)
**	RIGHT	(direction = 1)
**	UP		(direction = 2)
**	DOWN	(direction = 3)
**
**	The cursor will be moved in 'direction' a total of 'n_times' except if
**	the cursor hits the start or end position of the e->buffer.
*/

void	move_cursor(t_env *e, int direction, size_t n_times)
{
	size_t	n_fl_chars;

	n_fl_chars = ft_strchr(e->buffer, '\n') - e->buffer + 1;
	while (n_times--)
	{
		if (direction == 0 && e->cursor > e->buffer_lock)
			move_left(e, n_fl_chars);
		else if (direction == 1 && e->cursor < e->buffer_end)
			move_right(e, n_fl_chars);
		else if (direction == 2)
			move_up(e);
		else if (direction == 3)
			move_down(e);
	}
}
