/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:08:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 16:19:24 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H
# define HASHMAP_SIZE	256

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

typedef struct			s_hashmap
{
	t_hash_node			*nodes[HASHMAP_SIZE];
}						t_hashmap;

typedef struct			s_env
{
	t_hashmap			map;
}						t_env;	

/*
**	main.c
*/

void					sh_loop();

/*
**	env.c
*/

void					init_sh(char **envp);

/*
**	listen.c
*/

void					sh_listen();

/*
**	parse.c
*/

void					sh_parse();

/*
**	dispatcher.c
*/

void					sh_dispatcher();

/*
**	hashmap_utils.c
*/
unsigned long			djb2_hash(char *str);
t_hash_node				*new_hash_node(char *key, char *val);
t_hash_node 			*get_hash_node(t_hashmap hmap, char *key);
int						add_hash_node(t_hashmap hmap, char *key, char *value);
int						remove_hash_node(t_hashmap hmap, char *key);

#endif
