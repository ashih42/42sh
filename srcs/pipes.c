#include "ft_42sh.h"

static void	pipe_output(t_env *e, char ***cmds, size_t *i)
{
	int		fd;

	if (!ft_strcmp(cmds[*i + 1][0], ">"))
	{
		(e->redir_out != -1) ? close(e->redir_out) : 0;
		if ((fd = open(cmds[*i + 2][0],
			O_WRONLY | O_CREAT | O_TRUNC, 0755)) < 0)
			ft_printf("42sh: failed to create file: %s\n", cmds[*i + 2][0]);
		else
			e->redir_out = fd;
	}
}

static void	pipe_append(t_env *e, char ***cmds, size_t *i)
{
	int		fd;

	if (!ft_strcmp(cmds[*i + 1][0], ">>"))
	{
		(e->redir_out != -1) ? close(e->redir_out) : 0;
		if ((fd = open(cmds[*i + 2][0],
			O_WRONLY | O_CREAT | O_APPEND, 0755)) < 0)
			ft_printf("42sh: failed to open file: %s\n", cmds[*i + 2][0]);
		else
			e->redir_out = fd;
	}
}

static void	pipe_input(t_env *e, char ***cmds, size_t *i)
{
	int		fd;

	if (!ft_strcmp(cmds[*i + 1][0], "<"))
	{
		(e->redir_out != -1) ? close(e->redir_out) : 0;
		if ((fd = open(cmds[*i + 2][0], O_RDONLY)) < 0)
			ft_printf("42sh: failed to open file: %s\n", cmds[*i + 2][0]);
		else
			e->fd = fd;
	}
}

void		setup_pipes(t_env *e, char ***cmds, size_t *i)
{
	while (cmds[*i + 1] && (!ft_strcmp(cmds[*i + 1][0], ">") ||
		!ft_strcmp(cmds[*i + 1][0], ">>") || !ft_strcmp(cmds[*i + 1][0], "<")))
	{
		if (!(cmds[*i + 2]))
			break ;
		pipe_output(e, cmds, i);
		pipe_append(e, cmds, i);
		pipe_input(e, cmds, i);
		*i += 2;
	}
	if (cmds[*i + 1] && !ft_strcmp(cmds[*i + 1][0], "|"))
	{
		(*i)++;
		e->pipe = 1;
	}
}
