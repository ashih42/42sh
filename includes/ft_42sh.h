/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:08:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 14:53:24 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H
# define HASHMAP_SIZE	512

/*
**	This will be the data structure that stores our environment variables
**	Maybe other stuff too?
*/

typedef struct			s_hash_node
{
	char				*key;
	char				*val;
	struct s_hash_node	*next;
}						t_hash_node;

typedef struct			s_env
{
	t_hash_node			env_hashmap[HASHMAP_SIZE];
}						t_env;	

/*
**	main.c
*/

void			sh_loop();

/*
**	env.c
*/

void			init_sh(char **envp);

/*
**	listen.c
*/

void			sh_listen();

/*
**	parse.c
*/

void			sh_parse();

/*
**	dispatcher.c
*/

void			sh_dispatcher();

#endif
