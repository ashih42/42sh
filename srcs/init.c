/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:47 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 19:15:12 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	init_sh()
**
**	This function should read in the default shell environment variables
**	(**envp) and load them into our 42sh environment variable data structure...
*/

void	init_sh(t_env *e, char **envp)
{
	char	*tmp_key;
	char	*tmp_val;
	char	*eq_ptr;

	printf("%lu %lu\n", djb2_hash("playwright"), djb2_hash("snush"));

	while (*envp)
	{
		eq_ptr = ft_strchr(*envp, '=');
		tmp_key = ft_strsub(*envp, 0, eq_ptr - (*envp));
		//printf("key: |%s|\n", tmp_key);
		tmp_val = ft_strdup(eq_ptr + 1);
		//printf("val: |%s|\n", tmp_val);
		envp++;
		add_hash_node(&e->map, tmp_key, tmp_val);
		free(tmp_key);
		free(tmp_val);
	}
	printf("test key: |%s|\n", get_hash_node(&e->map, "OLDPWD")->key);
	printf("test val: |%s|\n", get_hash_node(&e->map, "OLDPWD")->val);
	printf("test key: |%s|\n", get_hash_node(&e->map, "HOME")->key);
	printf("test val: |%s|\n", get_hash_node(&e->map, "HOME")->val);
	printf("test key: |%s|\n", get_hash_node(&e->map, "playwright")->key);
	printf("test val: |%s|\n", get_hash_node(&e->map, "playwright")->val);
	printf("test key: |%s|\n", get_hash_node(&e->map, "snush")->key);
	printf("test val: |%s|\n", get_hash_node(&e->map, "snush")->val);
	remove_hash_node(&e->map, "snush");
	//printf("rem key: |%s|\n", get_hash_node(&e->map, "snush")->key);
	//printf("rem val: |%s|\n", get_hash_node(&e->map, "snush")->val);
	e->pwd = getcwd(0, 0);
}