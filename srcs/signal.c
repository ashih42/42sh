#include "ft_42sh.h"

void	ft_ctrl_c(int signo)
{
	(void)signo;
	if (g_e->child_pid != 0)
	{
		signal(SIGCHLD,SIG_IGN);
		kill(g_e->child_pid, SIGINT);
		g_e->child_pid = 0;
		ft_printf("\n");
	}
	else
		ft_printf("\n{robot} %s > ", get_variable(g_e, "PWD"));
	ft_bzero(g_e->buffer, g_e->buffer_size + 1);
	g_e->cursor = 0;
	g_e->buffer_end = 0;
}
