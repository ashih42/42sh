/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:59 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 08:13:13 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	built_ins(t_env *e, int argc, char **argv)
{
	if (ft_strequ(argv[0], "cd"))
		ft_cd(e, argc, argv);
	else if (ft_strequ(argv[0], "echo"))
		ft_echo(e, argc, argv);
	else if (ft_strequ(argv[0], "env"))
		ft_env(e, argc, argv);
	else if (ft_strequ(argv[0], "setenv"))
		ft_setenv(e, argc, argv);
	else if (ft_strequ(argv[0], "unsetenv"))
		ft_unsetenv(e, argc, argv);
	else if (ft_strequ(argv[0], "exit"))
		ft_exit(e, argc, argv);
	else
		return (0);
	return (1);
}

static char	*build_filepath(char *path, char *file)
{
	char	*filepath;

	if ((filepath = ft_strnew(ft_strlen(path) + 1 + ft_strlen(file))))
	{
		ft_strcpy(filepath, path);
		ft_strcat(filepath, "/");
		ft_strcat(filepath, file);
	}
	return (filepath);
}

int		fork_execve(char *path, char **argv, char **envp)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
		exit(execve(path, argv, envp));
	else if (pid != -1)
		waitpid(pid, &status, 0);
	return ((status == 0) ? 0 : -1);
}

// TO-DO NOTES:
// should separately check:
// 1. does the command/file exist?
// 2. does it have permissions?
// and print corresponding error message

// Also, how does, e.g.
// > ./foo
// the dot expands to current directory? 
// it seems the OS just knows what . and .. mean,
// so the shell doesn't have to do anything special about them

int		execute(t_env *e, char **argv, char **envp)
{
	char	*temp_path;
	char	**path;
	size_t	i;

	temp_path = get_variable(e, "PATH");
	if (!ft_strchr(argv[0], '/'))
	{
		if ((path = ft_strsplit(temp_path, ':')))
		{
			i = -1;
			while (path[++i])
			{
				temp_path = build_filepath(path[i], argv[0]);
				if (temp_path && access(temp_path, X_OK) == 0)
				{
					fork_execve(temp_path, argv, envp);
					free(temp_path);
					ft_char_array_del(path);
					return (0);
				}
				free(temp_path);
			}
			ft_char_array_del(path);
		}
		return (-1);
	}
	else
		return (fork_execve(argv[0], argv, envp));
}

void		sh_dispatcher(t_env *e, int argc, char **argv)
{
	char	**envp;

	if (argc && !built_ins(e, argc, argv))
	{
		if ((envp = serialize_envp(e)))
		{
			if (execute(e, argv, envp) < 0)
				ft_printf("42sh: command not found: %s\n", argv[0]);
			ft_char_array_del(envp);
		}
		else
			ft_printf("{robot} [!] Failed to allocate envp!\n");
		ft_char_array_del(argv);
	}
}
