/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:46:15 by apuel             #+#    #+#             */
/*   Updated: 2018/03/07 06:26:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_list	*new_entry(char *key, char *value)
{
	char	**entry;

	if ((entry = malloc(sizeof(char *) * 3)))
	{
		entry[0] = ft_strdup(key);
		entry[1] = ft_strdup(value);
		entry[2] = NULL;
		return (ft_lst_new_ref(entry, sizeof(char *) * 2));
	}
	return (NULL);
}

void			del_variable(t_env *e, char *key)
{
	t_list		*node;
	t_list		*prev;
	char 		**entry;

	// check if empty list
	if (e->envp == 0)
		return ;

	// check first node;
	entry = e->envp->content;
	if (ft_strequ(entry[0], key))
	{
		e->envp = e->envp->next;
		ft_char_array_del(entry);
		ft_memdel((void **)&node);
		return ;
	}
	// check second to last nodes
	prev = e->envp;
	node = e->envp->next;
	while (node != 0)
	{
		entry = node->content;
		if (ft_strequ(entry[0], key))
		{
			prev->next = node->next;
			ft_char_array_del(entry);
			ft_memdel((void **)&node);
			return ;
		}
		prev = node;
		node = node->next;
	}
	
}


char			*get_variable(t_env *e, char *key)
{
	t_list	*node;
	char	**entry;

	node = e->envp;
	while (node)
	{
		entry = node->content;
		if (ft_strcmp(entry[0], key) == 0)
			return (entry[1]);
		node = node->next;
	}
	return (NULL);
}

int				set_variable(t_env *e, char *key, char *value)
{
	t_list	*node;
	char	**entry;

	node = e->envp;
	while (node)
	{
		entry = node->content;
		if (ft_strcmp(entry[0], key) == 0)
		{
			free(entry[1]);
			entry[1] = ft_strdup(value);
			return (1);
		}
		node = node->next;
	}
	if ((node = new_entry(key, value)))
	{
		ft_lst_add_last(&(e->envp), node);
		return (1);
	}
	return (0);
}

char			**serialize_envp(t_env *e)
{
	t_list	*node;
	char	**table;
	char	**entry;
	char	*map;
	size_t	i;

	i = 0;
	node = e->envp;
	if ((table = ft_memalloc(sizeof(char *) * (ft_lst_size(e->envp) + 1))))
		while (node)
		{
			entry = node->content;
			if (!(map = ft_strnew(ft_strlen(entry[0]) + 1 + ft_strlen(entry[1]))))
			{
				ft_char_array_del(table);
				return (NULL);
			}
			ft_strcpy(map, entry[0]);
			ft_strcat(map, "=");
			ft_strcat(map, entry[1]);
			table[i++] = map;
			node = node->next;
		}
	return (table);
}
