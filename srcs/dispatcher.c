#include "ft_42sh.h"

/*
**	sh_dispatcher()
**
**	This function should take the cmds/arguments that the parser has identified:
**
**	1) Check if the command is a local one (i.e. builtin)
**	2) If it's not local, check if the cmd is located in PATH env folders
**	3) If the cmd is not located in the specified PATHS check if the the cmd was
**	   provided as a literal path.
*/

static int	built_in(t_env *e, int (*f)(t_env *, int, char **), int argc, char **argv)
{
	int		status;
	int		fd[2];
	int		stdin_fd;
	int		stdout_fd;

	status = -1;
	stdin_fd = -1;
	stdout_fd = -1;
	if (pipe(fd) < 0)
		ft_printf("42sh: failed to create pipe\n");
	else
	{
		if (e->fd != -1)
		{
			dup2(e->fd, STDIN_FILENO);
			stdin_fd = dup(STDIN_FILENO);
		}
		if (e->pipe || e->redir_out != -1)
			stdout_fd = dup(STDOUT_FILENO);
		if (e->pipe)
			dup2(fd[1], STDOUT_FILENO);
		if (e->redir_out != -1)
			dup2(e->redir_out, STDOUT_FILENO);
		status = f(e, argc, argv);
		if (stdin_fd != -1)
		{
			dup2(stdin_fd, STDIN_FILENO);
			close(stdin_fd);
		}
		if (stdout_fd != -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			close(stdout_fd);
		}
		if (e->pipe)
			e->fd = fd[0];
		else
			close(fd[0]);
		close(fd[1]);
	}
	if (e->fd != -1)
		close(e->fd);
	if (e->redir_out != -1)
		close(e->redir_out);
	return (status);
}

static int	built_ins(t_env *e, int argc, char **argv, int *status)
{
	if (ft_strequ(argv[0], "cd"))
		*status = built_in(e, ft_cd, argc, argv);
	else if (ft_strequ(argv[0], "echo"))
		*status = built_in(e, ft_echo, argc, argv);
	else if (ft_strequ(argv[0], "env"))
		*status = built_in(e, ft_env, argc, argv);
	else if (ft_strequ(argv[0], "setenv"))
		*status = built_in(e, ft_setenv, argc, argv);
	else if (ft_strequ(argv[0], "unsetenv"))
		*status = built_in(e, ft_unsetenv, argc, argv);
	else if (ft_strequ(argv[0], "exit"))
		*status = built_in(e, ft_exit, argc, argv);
	else if (ft_strequ(argv[0], "history"))
		*status = built_in(e, ft_history, argc, argv);
	else
		return (0);
	return (1);
}

int			fork_execve(t_env *e, char *path, char **argv, char **envp)
{
	int		pid;
	int		status;
	int		fd[2];

	status = -1;
	if (pipe(fd) < 0)
		ft_printf("42sh: failed to create pipe\n");
	else
	{
		pid = fork();
		if (pid < 0)
			ft_printf("42sh: failed to fork process\n");
		else if (pid == 0)
		{
			if (e->fd != -1)
			{
				dup2(e->fd, STDIN_FILENO);
				close(e->fd);
			}
			if (e->pipe)
				dup2(fd[1], STDOUT_FILENO);
			if (e->redir_out != -1)
			{
				dup2(e->redir_out, STDOUT_FILENO);
				close(e->redir_out);
			}
			close(fd[0]);
			close(fd[1]);
			exit(execve(path, argv, envp));
		}
		else
		{
			ft_lst_add_last(&(e->children_pids), ft_lst_new_ref((void *)1, pid));
			status = 0;
		}
		if (e->fd != -1)
			close(e->fd);
		if (e->pipe)
			e->fd = fd[0];
		else
			close(fd[0]);
		close(fd[1]);
	}
	if (e->fd != -1)
		close(e->fd);
	if (e->redir_out != -1)
		close(e->redir_out);
	return (status);
}

int		execute(t_env *e, char **argv, char **envp, int *status)
{
	char	*temp_path;
	char	**path;
	size_t	i;

	temp_path = get_variable(e, "PATH");
	if (!ft_strchr(argv[0], '/'))
	{
		if (temp_path && (path = ft_strsplit(temp_path, ':')))
		{
			i = -1;
			while (path[++i])
			{
				temp_path = build_filepath(path[i], argv[0]);
				if (temp_path && access(temp_path, X_OK) == 0)
				{
					*status = fork_execve(e, temp_path, argv, envp);
					free(temp_path);
					ft_char_array_del(path);
					return (0);
				}
				free(temp_path);
			}
			ft_char_array_del(path);
		}
		ft_printf("42sh: command not found: %s\n", argv[0]);
		return (-1);
	}
	if (access(argv[0], X_OK) == 0)
		*status = fork_execve(e, argv[0], argv, envp);
	else
	{
		if (errno & ENOENT)
			ft_printf("42sh: no such file or directory: %s\n", argv[0]);
		if (errno & EACCES)
			ft_printf("42sh: permission denied: %s\n", argv[0]);
		return (-1);
	}
	return (0);
}

void		setup_pipes(t_env *e, char ***cmds, size_t *i)
{
	int	fd;

	while (cmds[*i + 1] && (!ft_strcmp(cmds[*i + 1][0], ">") ||
		!ft_strcmp(cmds[*i + 1][0], ">>") || !ft_strcmp(cmds[*i + 1][0], "<")))
	{
		if (!(cmds[*i + 2]))
			break ;
		if (!ft_strcmp(cmds[*i + 1][0], ">"))
		{
			if (e->redir_out != -1)
				close(e->redir_out);
			if ((fd = open(cmds[*i + 2][0], O_WRONLY | O_CREAT | O_TRUNC, 0755)) < 0)
				ft_printf("42sh: failed to create file: %s\n", cmds[*i + 2][0]);
			else
				e->redir_out = fd;
		}
		else if (!ft_strcmp(cmds[*i + 1][0], ">>"))
		{
			if (e->redir_out != -1)
				close(e->redir_out);
			if ((fd = open(cmds[*i + 2][0], O_WRONLY)) < 0)
				ft_printf("42sh: failed to open file: %s\n", cmds[*i + 2][0]);
			else
			{
				lseek(fd, 0, SEEK_END);
				e->redir_out = fd;
			}
		}
		else if (!ft_strcmp(cmds[*i + 1][0], "<"))
		{
			if (e->fd != -1)
				close(e->fd);
			if ((fd = open(cmds[*i + 2][0], O_RDONLY)) < 0)
				ft_printf("42sh: failed to open file: %s\n", cmds[*i + 2][0]);
			else
				e->fd = fd;
		}
		ft_char_array_del(cmds[++(*i)]);
		ft_char_array_del(cmds[++(*i)]);
	}
	if (cmds[*i + 1] && !ft_strcmp(cmds[*i + 1][0], "|"))
	{
		ft_char_array_del(cmds[++(*i)]);
		e->pipe = 1;
	}
}

void		sh_dispatcher(t_env *e, char ***cmds)
{
	char	**envp;
	char	**argv;
	size_t	i;
	int		status;
	t_list	*pids;

	status = 0;
	i = -1;
	argv = NULL;
	e->fd = -1;
	e->redir_out = -1;
	while (cmds[++i])
	{
		if (argv)
			ft_char_array_del(argv);
		argv = cmds[i];
		if (i > 0)
		{
			if (argv[0][0] == ';')
				continue ;
			if (!ft_strcmp(argv[0], "||"))
			{
				if (!status)
					break ;
				continue ;
			}
			if (!ft_strcmp(argv[0], "&&"))
			{
				if (status)
					break ;
				continue ;
			}
		}
		setup_pipes(e, cmds, &i);
		if (!built_ins(e, ft_char_array_length(argv), argv, &status))
		{
			if ((envp = serialize_envp(e)))
			{
				if (execute(e, argv, envp, &status) < 0)
					status = -1;
				ft_char_array_del(envp);
			}
			else
			{
				ft_printf("42sh: failed to allocate memory for envp\n");
				status = -1;
			}
		}
		if (!(e->pipe))
		{
			pids = e->children_pids;
			while (pids)
			{
				waitpid(pids->content_size, &status, 0);
				pids = pids->next;
			}
			ft_lstdel(&(e->children_pids), NULL);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else
				status = -1;
		}
		ft_char_array_del(argv);
		argv = NULL;
		e->pipe = 0;
	}
	if (argv)
		ft_char_array_del(argv);
	e->pipe = 0;
	if (e->fd != -1)
		close(e->fd);
	if (e->redir_out != -1)
		close(e->redir_out);
	pids = e->children_pids;
	while (pids)
	{
		waitpid(pids->content_size, &status, 0);
		pids = pids->next;
	}
	ft_lstdel(&(e->children_pids), NULL);
}
