#include "ft_42sh.h"

static void  built_in_else(t_env *e, t_built_in *bi)
{
	if (e->fd != -1)
		bi->stdin_fd = dup(STDIN_FILENO);
	dup3(e->fd, STDIN_FILENO);
	e->fd = -1;
	if (e->pipe || e->redir_out != -1)
		bi->stdout_fd = dup(STDOUT_FILENO);
	if (e->pipe)
		dup2(bi->fd[1], STDOUT_FILENO);
	if (e->redir_out != -1)
		dup2(e->redir_out, STDOUT_FILENO);
	bi->status = bi->f(e, bi->argc, bi->argv);
	dup3(bi->stdin_fd, STDIN_FILENO);
	dup3(bi->stdout_fd, STDOUT_FILENO);
	if (e->pipe)
		e->fd = bi->fd[0];
	else
		close(bi->fd[0]);
	close(bi->fd[1]);
}

static int	built_in(t_env *e, int (*f)(t_env *, int, char **),
	int argc, char **argv)
{
	t_built_in bi;

	bi.status = -1;
	bi.stdin_fd = -1;
	bi.stdout_fd = -1;
	bi.f = f;
	bi.argc = argc;
	bi.argv = argv;
	if (pipe(bi.fd) < 0)
	{
		ft_printf("42sh: failed to create pipe\n");
		if (e->fd != -1)
			close(e->fd);
		e->fd = -1;
	}
	else
		built_in_else(e, &bi);
	if (e->redir_out != -1)
		close(e->redir_out);
	e->redir_out = -1;
	return (bi.status);
}

int	built_ins(t_env *e, int argc, char **argv, int *status)
{
	if (ft_strequ(argv[0], "cd"))
		*status = built_in(e, ft_cd, argc, argv);
	else if (ft_strequ(argv[0], "echo"))
		*status = built_in(e, ft_echo, argc, argv);
	else if (ft_strequ(argv[0], "env"))
		*status = built_in(e, ft_env, argc, argv);
	else if (ft_strequ(argv[0], "setenv") ||
		ft_strequ(argv[0], "export"))
		*status = built_in(e, ft_setenv, argc, argv);
	else if (ft_strequ(argv[0], "unsetenv") ||
		ft_strequ(argv[0], "unset"))
		*status = built_in(e, ft_unsetenv, argc, argv);
	else if (ft_strequ(argv[0], "exit"))
		*status = built_in(e, ft_exit, argc, argv);
	else if (ft_strequ(argv[0], "history"))
		*status = built_in(e, ft_history, argc, argv);
	else
		return (0);
	return (1);
}
