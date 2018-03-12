#include "ft_42sh.h"

/*
**	job_control_set_to_foreground()
**
**	https://www.gnu.org/software/libc/manual/html_node/Initializing-the-
**	Shell.html
**	https://unix.stackexchange.com/questions/404054/how-is-a-process-group-id
**	-set
**
**	This function ensures the interactive shell is the foreground process.
**
*/

static void			job_control(t_env *e)
{
	pid_t			shell_pgid;
	struct termios	shell_tmodes;
	bool			shell_terminal;
	bool			shell_is_interactive;

	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive)
	{
		while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			ft_printf("Couldn't put the shell in its own process group\n");
			exit(1);
		}
		tcsetpgrp(shell_terminal, shell_pgid);
		tcgetattr(shell_terminal, &shell_tmodes);
		e->job = job_new();
	}
}

/*
**	sh_init()
**
**	This function should read in the default shell environment variables
**	(**envp) and load them into our 42sh environment variable data structure...
**
**	Essentially deserialize envp.
*/

void				sh_init(t_env *e, char **envp)
{
	char			*tmp_key;
	char			*tmp_val;
	char			*eq_ptr;

	job_control(e);
	while (*envp)
		if ((eq_ptr = ft_strchr(*envp, '=')))
		{
			if ((tmp_key = ft_strsub(*envp, 0, eq_ptr - (*envp))) &&
					(tmp_val = ft_strdup(eq_ptr + 1)))
			{
				set_variable(e, tmp_key, tmp_val);
				free(tmp_val);
				free(tmp_key);
			}
			envp++;
		}
	tmp_val = getcwd(NULL, 0);
	set_variable(e, "PWD", tmp_val);
	if (!get_variable(e, "OLDPWD"))
		set_variable(e, "OLDPWD", tmp_val);
	free(tmp_val);
}
