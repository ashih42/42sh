/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:08:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 19:28:29 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H


# include <stdio.h>		// REMOVE THIS LATER 

# include <libft.h>


# define HASHMAP_SIZE	256
# define BUFFER_SIZE	4096
# define WHITESPACE		" \t\n\v\r\f"

# define SWAP(a, b, T) {T temp = (a); (a) = (b); (b) = temp;}


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
	char				buffer[BUFFER_SIZE + 1];
	int					pos;
	char				**args;
	char				*pwd;
	char				*oldpwd;
}						t_env;	

/*
**	main.c
*/

void					sh_loop(t_env *e);

/*
**	env.c
*/

void					init_sh(t_env *e, char **envp);

/*
**	listen.c
*/

void					sh_listen(t_env *e);

/*
**	parse.c
*/

void					sh_parse(t_env *e);

/*
**	dispatcher.c
*/

void					sh_dispatcher(t_env *e);

/*
**	hashmap_utils.c
*/
unsigned long			djb2_hash(char *str);
t_hash_node				*new_hash_node(char *key, char *val);
t_hash_node 			*get_hash_node(t_hashmap *hmap, char *key);
int						add_hash_node(t_hashmap *hmap, char *key, char *value);
int						remove_hash_node(t_hashmap *hmap, char *key);

/*
**	split_ws.c
*/
char					**split_ws(char const *s, char *ws);

#endif
