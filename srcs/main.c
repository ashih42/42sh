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

char 	*get_money_key(char *expr)
{
	int i;
	char *key;
	
	if (expr[0] != '$')
		return (NULL);
	i = 1;
	while (ft_isalpha(expr[i]) || ft_isdigit(expr[i]) || expr[i] == '_')
		i++;
	key = ft_strnew(i - 1);
	ft_strncpy(key, expr + 1, i - 1);
	return (key);
}


void	replace_monies(t_env *e)
{
	int i;
	char *var;
	char *temp;
	char *money_key;
	char *money_value;

	i = 0;
	while (e->buffer[i])
	{
		money_key = get_money_key(e->buffer + i);
		if (money_key)
		{
			money_value = get_variable(e, money_key);
			money_value = (money_value) ? money_value : "";
			while ((ft_strlen(e->buffer) +
				ft_strlen(money_value) - ft_strlen(money_key) - 1) > e->buffer_size)
				extend_buffer(e);
			ft_memmove(e->buffer + i + ft_strlen(money_value),
				e->buffer + i + ft_strlen(money_key) + 1,
				ft_strlen(e->buffer + i + ft_strlen(money_key)));
			ft_strncpy(e->buffer + i, money_value, ft_strlen(money_value));
			ft_strdel(&money_key);
			i += ft_strlen(money_value);
		}
		else
		{
			i++;
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	e;
	char	***cmds;

	g_e = &e;
	signal(SIGINT, ft_ctrl_c);
//	signal(SIGTSTP, ft_ctrl_z);
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
				add_cmd_history(&e);
				replace_monies(&e);
				cmds = sh_parse(&e);
				if (cmds)
				{
					sh_dispatcher(&e, cmds);
					free(cmds);
				}
			}
		}
	}
	return (0);
}
