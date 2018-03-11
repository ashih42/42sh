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

	g_e = &e;
	signal(SIGINT, ft_ctrl_c);
	signal(SIGTSTP, ft_ctrl_z);
	ft_bzero(&e, sizeof(t_env));
	if ((e.buffer = malloc(BUFFER_SIZE + 1)))
	{
		e.buffer_size = BUFFER_SIZE;
		sh_init(&e, envp);
		while (1)
		{
			e.history_pos = NULL;
			sh_listen(&e);
			//Need to do stuff with the return of history_bang_exploder
			history_bang_exploder(&e);
			if (!e.buffer)
				break ;
			argv = sh_parse(&e);
			if (argv)
				sh_dispatcher(&e, ft_char_array_length(argv), argv);
		}
	}
	return (0);
}
