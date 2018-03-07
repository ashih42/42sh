/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:08:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 06:19:14 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

# define HASHMAP_SIZE	256
# define BUFFER_SIZE	4096
# define WHITESPACE		" \t\n\v\r\f"

typedef struct			s_env
{
	t_list				*envp;
	char				*buffer;
}						t_env;	

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
**	listen.c
*/
void					sh_listen(t_env *e);

/*
**	parse.c
*/
char					**sh_parse(t_env *e, int *argc);

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
**	split_argv.c
*/

char					**split_argv(char const *s, char *ws, int *argc);

#endif
