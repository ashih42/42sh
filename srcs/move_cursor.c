#include "ft_42sh.h"

/*
**	move_left()
**
**	Function to move our cursor left. Can also handle 'leftward' traversal of
**	multiline content.
**
**	'\027[F'	Cursor Prev Line
**	'\027[E'	Cursor Next Line
*/

static void	move_left(t_env *e, size_t n_fl_chars)
{
	size_t	n_chars;
	int		i;

	if (e->buffer[--e->cursor] == '\n')
	{
		ft_putstr("\x1B[F");
		n_chars = chars_until_newline(e, e->cursor - 1, 0) + 1;
		while (n_chars--)
			ft_putstr("\x1B[C");
		i = -1;
		if (e->cursor < n_fl_chars)
			while (++i <= e->promt_len)
				ft_putstr("\x1B[C");
	}
	ft_putstr("\x1B[D");
}

/*
**	move_right()
**
**	Function to move our cursor right. Can also handle 'rightward' traversal of
**	multiline content.
**
**	'\027[F'	Cursor Prev Line
**	'\027[E'	Cursor Next Line
*/

static void	move_right(t_env *e)
{
	if (e->buffer[e->cursor] == '\n')
		ft_putstr("\x1B[E\r");
	else
		ft_putstr("\x1B[C");
	e->cursor++;
}

static void	move_up(t_env *e, size_t n_fl_chars, size_t num_nl)
{
	int	i;

	if (e->cursor < n_fl_chars || n_fl_chars == 0)
	{
		move_cursor(e, 1, e->buffer_end);
		while (num_nl--)
			ft_putstr("\r\x1B[K\x1B[F");
		get_cmd_history(e, 0);
	}
	else
	{
		e->cursor -= chars_until_newline(e, e->cursor - 1, 0) + 2;
		ft_putstr("\r\x1B[A");
		e->cursor -= chars_until_newline(e, e->cursor, 0);
		if (e->buffer[e->cursor] == '\n')
			e->cursor++;
		i = -1;
		if (e->cursor < n_fl_chars)
			while (++i < e->promt_len)
				ft_putstr("\x1B[C");
	}
}

static void	move_down(t_env *e, size_t n_lnl_pos, size_t num_nl)
{
	if (e->cursor > n_lnl_pos || n_lnl_pos == 0)
	{
		move_cursor(e, 1, e->buffer_end);
		while (num_nl--)
			ft_putstr("\r\x1B[K\x1B[F");
		get_cmd_history(e, 1);
	}
	else
	{
		e->cursor += chars_until_newline(e, e->cursor, 1) + 1;
		ft_putstr("\x1B[B\r");
	}
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
**
**	n_flcs = number of chars on the first line (first line characters)
**	n_lnl_pos = number of chars until last '\n' (last newline position)
*/

void	move_cursor(t_env *e, int direction, size_t n_times)
{
	size_t	num_nl;
	size_t	n_flcs;
	size_t	n_lnl_pos;

	num_nl = ft_count_occurrences(e->buffer, '\n');
	n_flcs = (num_nl) ? ft_fst_occ_idx(e->buffer, '\n') + 1 : e->buffer_end + 1;
	n_lnl_pos = (num_nl) ? ft_lst_occ_idx(e->buffer, '\n') : 0;
	while (n_times--)
	{ 
		if (direction == 0 && e->cursor > e->buffer_lock)
			move_left(e, n_flcs);
		else if (direction == 1 && e->cursor < e->buffer_end)
			move_right(e);
		else if (direction == 2 && !e->buffer_lock)
			move_up(e, n_flcs, num_nl);
		else if (direction == 3 && !e->buffer_lock)
			move_down(e, n_lnl_pos, num_nl);
	}
}
