#ifndef FT_42SH_H
# define FT_42SH_H

# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/types.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

# define HASHMAP_SIZE	256
# define BUFFER_SIZE	4096
# define WHITESPACE		" \t\n\v\r\f"
# define DELIM 			"\"'|<>"
# define INVALID_COLOR	-1

typedef struct			s_env
{
	t_list				*envp;
	t_list				*tab_execs;
	t_list				*tab_dir;
	t_list				*tab_pos;
	int					tab_mode;
	int					reset_tab_auto;
	t_dl_list			*cmd_history;
	t_dl_list			*history_end;
	t_dl_list			*history_pos;
	char				*buffer;
	int					promt_len;
	size_t				cursor;
	size_t				buffer_end;
	size_t				buffer_lock;
	size_t				buffer_size;
	t_list				*children_pids;
	pid_t				child_pid;
	pid_t				shell_pgid;
	pid_t				shell_stopped;
	struct termios		shell_tmodes;
	bool				shell_terminal;
	bool				shell_is_interactive;
	bool				pipe;
	int					fd;
	int					redir_out;
}						t_env;

typedef struct			s_add_terms
{
	int					head;
	int					i;
	int					inc;
	char				*work_buf;
	char				*word;
	char				quote;
}						t_add_terms;

typedef struct			s_built_in
{
	int					status;
	int					fd[2];
	int					stdin_fd;
	int					stdout_fd;
	int					(*f)(t_env *, int, char **);
	int					argc;
	char				**argv;
}						t_built_in;

typedef struct			s_fork_execve
{
	int					pid;
	int					status;
	int					fd[2];
	char				*path;
	char				**argv;
	char				**envp;
}						t_fork_execve;

typedef struct			s_exec
{
	char				*temp_path;
	char				**path;
	size_t				i;
	int					*status;
	int					ret;
}						t_exec;

typedef struct			s_dsp
{
	char				**envp;
	char				**argv;
	size_t				i;
	int					status;
	t_list				*pids;
}						t_dsp;

typedef struct 			s_sprf
{
	t_list 				*list;
	t_list 				*prev;
	t_list 				*next;
	t_list 				*head;
	char				*str;
}						t_sprf;

typedef struct 			s_strf
{
	char				*head;
	char				*mid;
	char				*tail;
	t_list				*mid_list;
	t_list				*mid_list_head;
	char				*temp;
	char				*del;
}						t_strf;

t_env					*g_e;

/*
**	path_utils.c
**	Used by dispatcher.c and tab_autocomplete.c
*/
char					*build_filepath(char *path, char *file);
int						is_dir(char *path);

/*
**	term_utils.c
**	Used by listen.c, ft_history.c, and tab_autocomplete.c
*/
void					enable_raw_mode(struct termios *orig_termios);
void					disable_raw_mode(struct termios *orig_termios);
void					clear_and_update_term(t_env *e, char *new_str);
void					insert_and_update_term(t_env *e, char *new, size_t pos);
size_t 					chars_until_newline(t_env *e, size_t cur_pos,
											int direction);

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
**	move_cursor.c
*/
void					move_cursor(t_env *e, int direction, size_t n_times);

/*
**	listen.c
*/
void					sh_listen(t_env *e);

/*
**	listen_utils.c
*/
int						extend_buffer(t_env *e);
int						handle_esc_seq(t_env *e, char c);
int						char_specs(t_env *e, char c);
int						submit_attempt(t_env *e);

/*
**	parse.c
*/
char					***sh_parse(t_env *e);

/*
**	dispatcher.c
*/
void					sh_dispatcher(t_env *e, char ***cmds);

/*
**	pipes.c
*/
void					setup_pipes(t_env *e, char ***cmds, size_t *i);

/*
**	execute.c
*/
int						execute(t_env *e, char **argv, char **envp,
							int *status);

/*
**	built_ins.c
*/
int						built_ins(t_env *e, int argc, char **argv, int *status);

/*
**	ft_cd.c
*/
int						ft_cd(t_env *e, int argc, char **argv);

/*
**	ft_echo.c
*/
int						ft_echo(t_env *e, int argc, char **argv);

/*
**	ft_env.c
*/
int						ft_env(t_env *e, int argc, char **argv);

/*
**	ft_setenv.c
*/
int						ft_setenv(t_env *e, int argc, char **argv);

/*
**	ft_unsetenv.c
*/
int						ft_unsetenv(t_env *e, int argc, char **argv);

/*
**	ft_exit.c
*/
int						ft_exit(t_env *e, int argc, char **argv);

/*
**	signal.c
*/
void					ft_ctrl_c(int signo);

/*
**	ft_history.c
*/
int						add_cmd_history(t_env *e);
int						ft_history(t_env *e, int argc, char **argv);
void					get_cmd_history(t_env *e, int mode);

/*
**	ft_history_bang_exploder.c
*/
int						history_bang_exploder(t_env *e);

/*
**	tab_autocomplete.c
*/
t_list					*get_dir_contents(char *dir_path, int e_mode);
char					*get_curr_word(t_env *e, size_t cursor_pos);
int						tab_autocomplete(t_env *e);

/*
**	split_argv.c
*/
char					**split_argv(char const *s, char *ws);

/*
**	strip_argv.c
*/
void					strip_argv(char **argv);

/*
**	ft_super_factory.c
*/
t_list					*ft_super_factory(char *s);

/*
**	match.c
*/
int						valid_brackets(char *s);
int						should_glob(char *s2);
int						match(char *s1, char *s2);

/*
**	split_dirs.c
*/
char					**split_dirs(char const *s);

/*
**	ft_glob.c
*/
t_list					*ft_glob(char *s2);

/*
** globber system
*/
int						matchparse(char *s1, char *s2);
size_t					init_parse(char *s1, char *s2);
t_list					*get_dir_contents_search(char *dir_path, int ac,
							char **argv);

/*
**	debug.c
*/
void					print_list(t_list *list);
void					print_expr_list(t_list *expr_list);
void					print_char2d(char **array);
void					print_char4d(char ****array);

#endif
