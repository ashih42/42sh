#ifndef FT_42SH_H
# define FT_42SH_H

# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <stdbool.h>
# include "libft.h"

# define HASHMAP_SIZE	256
# define BUFFER_SIZE	4096
# define WHITESPACE		" \t\n\v\r\f"
# define DELIM 			"\"'|<>"

typedef struct			s_env
{
	t_list				*envp;
	t_dl_list			*cmd_history;
	t_dl_list			*history_end;
	t_dl_list			*history_pos;
	char				*buffer;
	size_t				cursor;
	size_t				buffer_end;
	size_t				buffer_size;
	int					child_pid;
}						t_env;

typedef struct			s_process
{
	struct s_process	*next;/* next process in pipeline */
	char				**argv;/* for exec */
	pid_t				pid;/* process ID */
	bool				completed;/* true if process has completed */
	bool				stopped;/* true if process has stopped */
	int					status;/* reported status value */
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;/* next active job */
	char				*command;/* command line, used for messages */
	t_process			*first_process;/* list of processes in this job */
	pid_t				pgid;/* process group ID */
	bool				notified;/* true if user told about stopped job */
	struct termios		tmodes;/* saved terminal modes */
}						t_job;

t_env					*g_e;

/*
**	envp.c
*/
void					del_variable(t_env *e, char *key);
char					*get_variable(t_env *e, char *key);
int						set_variable(t_env *e, char *key, char *value);
char					**serialize_envp(t_env *e);

/*
**	init.c
*/
void					sh_init(t_env *e, char **envp);

/*
**	job_control_utils.c
*/
t_job					*find_job(pid_t pgid);
bool					job_is_stopped(t_job *j);
bool					job_is_completed(t_job *j);

/*
**	listen.c
*/
void					sh_listen(t_env *e);

/*
**	parse.c
*/
char					**sh_parse(t_env *e);

/*
**	dispatcher.c
*/
void					sh_dispatcher(t_env *e, int argc, char **argv);

/*
**	ft_cd.c
*/
void					ft_cd(t_env *e, int argc, char **argv);

/*
**	ft_echo.c
*/
void					ft_echo(t_env *e, int argc, char **argv);

/*
**	ft_env.c
*/
void					ft_env(t_env *e, int argc, char **argv);

/*
**	ft_setenv.c
*/
void					ft_setenv(t_env *e, int argc, char **argv);

/*
**	ft_unsetenv.c
*/
void					ft_unsetenv(t_env *e, int argc, char **argv);

/*
**	ft_exit.c
*/
void					ft_exit(t_env *e, int argc, char **argv);

/*
**	signal.c
*/
void					ft_ctrl_c(int signo);
void					ft_ctrl_z(int signo);

/*
**	ft_history.c
*/
int						add_cmd_history(t_env *e);
void					ft_history(t_env *e, int argc, char **argv);
void					get_cmd_history(t_env *e, int mode);

/*
**	ft_history_bang_exploder.c
*/
int						history_bang_exploder(t_env *e);

/*
**	split_argv.c
*/
char					**split_argv(char const *s, char *ws);

/*
**	str_explode.c
*/
void					str_explode(char *s, t_list **list);

/*
**	redir.c
*/
int 					redir_input(char **expr, char *filename);
int 					redir_output(char **expr, char *filename);
int 					redir_append(char **expr, char *filename);
int						pipe_exprs(char **expr1, char **expr2);

/*
**	debug.c
*/
void					print_list(t_list *list);
void					print_expr_list(t_list *expr_list);

#endif
