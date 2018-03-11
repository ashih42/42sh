#include "ft_42sh.h"

/*
**	main()
**
**	Our shell loop which consists of:
**
**	1) Listening for user input on stdin
**	2) Parsing the input
**	3) Calling the relevant commands specified in the parsed input
*/

int		main(int argc, char **argv, char **envp)
{
	t_env	e;
	char	****cmds;

	g_e = &e;
	signal(SIGINT, ft_ctrl_c);
	signal(SIGSTOP, ft_ctrl_z);
	ft_bzero(&e, sizeof(t_env));
	if ((e.buffer = malloc(BUFFER_SIZE + 1)))
	{
		e.buffer_size = BUFFER_SIZE;
		sh_init(&e, envp);
		while (1)
		{
			e.history_pos = NULL;
			sh_listen(&e);
			if (!e.buffer)
				break ;
			if (history_bang_exploder(&e) != -1)
			{
				cmds = sh_parse(&e);
				if (cmds)
					sh_dispatcher(&e, cmds);
			}
		}
	}
	return (0);
}
