#include "ft_42sh.h"

void	ft_ctrl_c(int signo)
{
	t_list	*pids;

	(void)signo;
	if (g_e->children_pids)
	{
		signal(SIGCHLD, SIG_IGN);
		pids = g_e->children_pids;
		while (pids)
		{
			kill(pids->content_size, SIGINT);
			pids = pids->next;
		}
		ft_putchar('\n');
	}
	else
	{
		move_cursor(g_e, 1, g_e->buffer_end - g_e->cursor);
		g_e->promt_len = ft_printf("\n{robot} %s > ", get_variable(g_e, "PWD"));
		ft_bzero(g_e->buffer, g_e->buffer_size + 1);
		g_e->cursor = 0;
		g_e->buffer_end = 0;
	}
}
