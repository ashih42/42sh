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

static int	built_ins(t_env *e, int argc, char **argv, int *status)
{
	if (ft_strequ(argv[0], "cd"))
	{
		*status = ft_cd(e, argc, argv);
		return (1);
	}
	else if (ft_strequ(argv[0], "echo"))
		ft_echo(e, argc, argv);
	else if (ft_strequ(argv[0], "env"))
		ft_env(e, argc, argv);
	else if (ft_strequ(argv[0], "setenv"))
	{
		*status = ft_setenv(e, argc, argv);
		return (1);
	}
	else if (ft_strequ(argv[0], "unsetenv"))
		ft_unsetenv(e, argc, argv);
	else if (ft_strequ(argv[0], "exit"))
		ft_exit(e, argc, argv);
	else if (ft_strequ(argv[0], "history"))
		ft_history(e, argc, argv);
	else
		return (0);
	*status = 0;
	return (1);
}

int			fork_execve(t_env *e, char *path, char **argv, char **envp)
{
	int		pid;
	int		status;
	t_list	*pointer;

	status = -1;
	pid = fork();
	e->child_pid = pid;
	if (pid < 0)
		ft_printf("42sh: failed to fork process\n");
	else if (pid == 0)
		exit(execve(path, argv, envp));
	else
	{
		waitpid(pid, &status, 0);
		e->child_pid = 0;
	}
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

void		sh_dispatcher(t_env *e, char ***cmds)
{
	char	**envp;
	char	**argv;
	size_t	i;
	int		status;

	status = 0;
	i = -1;
	argv = NULL;
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
		//setup_pipes(cmds, &i);
		if (!built_ins(e, ft_char_array_length(argv), argv, &status))
		{
			if ((envp = serialize_envp(e)))
			{
				if (execute(e, argv, envp, &status) < 0 ||
					status < 0 || !WIFEXITED(status))
					status = -1;
				else
					status = WEXITSTATUS(status);
				ft_char_array_del(envp);
			}
			else
			{
				ft_printf("42sh: failed to allocate memory for envp\n");
				status = -1;
			}
		}
		ft_char_array_del(argv);
		argv = NULL;
	}
	if (argv)
		ft_char_array_del(argv);
}
