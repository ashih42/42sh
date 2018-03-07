#include "ft_42sh.h"

// There appears to be no way to pass arguments into this signal-handling function,
// already defined to only take 1 int parameter.

// So, I made a global pointer to t_env e.  Perhaps we could just use this global for everything?
// Or keep pasing e in arguments, and only use g_e for signals when absolutely necessary?

void	ft_ctrl_c(int signo)
{
	(void)signo;
	ft_printf("\n");
	
	// DELIVER DEMOCRACY?

	sh_listen(g_e);
}

void	ft_ctrl_z(int signo)
{
	void(signo);
	ft_printf("\n");

	sh_listen(g_e);
}
