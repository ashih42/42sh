#include "ft_42sh.h"

static void		do_child(t_env *e, t_fork_execve *fe)
{
	if (fe->pid == 0)
	{
		dup3(e->fd, STDIN_FILENO);
		if (e->pipe)
			dup2(fe->fd[1], STDOUT_FILENO);
		dup3(e->redir_out, STDOUT_FILENO);
		close(fe->fd[0]);
		close(fe->fd[1]);
		exit(execve(fe->path, fe->argv, fe->envp));
	}
}

static void		do_pipe_and_fork(t_env *e, t_fork_execve *fe)
{
	if (pipe(fe->fd) < 0)
	{
		ft_printf("42sh: failed to create pipe\n");
		if (e->fd != -1)
			close(e->fd);
		e->fd = -1;
	}
	else
	{
		if ((fe->pid = fork()) < 0)
			ft_printf("42sh: failed to fork process\n");
		else
		{
			do_child(e, fe);
			ft_lst_add_last(&(e->children_pids),
				ft_lst_new_ref((int *)1, fe->pid));
			fe->status = 0;
		}
		(e->fd != -1) ? close(e->fd) : 0;
		e->fd = -1;
		(e->pipe) ? e->fd = fe->fd[0] : close(fe->fd[0]);
		close(fe->fd[1]);
	}
}

static int		fork_execve(t_env *e, char *path, char **argv, char **envp)
{
	t_fork_execve fe;

	fe.status = -1;
	fe.path = path;
	fe.argv = argv;
	fe.envp = envp;
	do_pipe_and_fork(e, &fe);
	if (e->redir_out != -1)
		close(e->redir_out);
	e->redir_out = -1;
	return (fe.status);
}

static int		path_execute(t_env *e, char **argv, char **envp, t_exec *ex)
{
	ex->temp_path = get_variable(e, "PATH");
	if (!ft_strchr(argv[0], '/'))
	{
		if (ex->temp_path && (ex->path = ft_strsplit(ex->temp_path, ':')))
		{
			ex->i = -1;
			while (ex->path[++(ex->i)])
			{
				ex->temp_path = build_filepath(ex->path[ex->i], argv[0]);
				if (ex->temp_path && !is_dir(ex->temp_path) &&
					access(ex->temp_path, X_OK) == 0)
				{
					*(ex->status) = fork_execve(e, ex->temp_path, argv, envp);
					free(ex->temp_path);
					ft_char_array_del(ex->path);
					return (0);
				}
				free(ex->temp_path);
			}
			ft_char_array_del(ex->path);
		}
		ft_printf("42sh: command not found: %s\n", argv[0]);
		return (-1);
	}
	return (42);
}

int				execute(t_env *e, char **argv, char **envp, int *status)
{
	t_exec		ex;

	ex.status = status;
	if ((ex.ret = path_execute(e, argv, envp, &ex)) <= 0)
		return (ex.ret);
	if (is_dir(argv[0]))
	{
		ft_printf("42sh: permission denied: %s\n", argv[0]);
		return (-1);
	}
	else if (access(argv[0], X_OK) == 0)
		*status = fork_execve(e, argv[0], argv, envp);
	else
	{
		if (errno == ENOENT)
			ft_printf("42sh: no such file or directory: %s\n", argv[0]);
		if (errno == EACCES)
			ft_printf("42sh: permission denied: %s\n", argv[0]);
		return (-1);
	}
	return (0);
}
