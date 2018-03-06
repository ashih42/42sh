/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:55:36 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 15:42:19 by hiroshius        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

t_hash_node		*new_hash_node(char *key, char *val)
{
	t_hash_node *new;
	char		*key_copy;
	char		*val_copy;

	if ((new = (t_hash_node *)malloc(sizeof(t_hash_node))))
	{
		key_copy = ft_strdup(key);
		val_copy = ft_strdup(value);
		if (key_copy && val_copy)
		{
			new->key = key_copy;
			new->val = val_copy;
			new->next = NULL;
		}
		else
		{
			if (key_copy)
				free(key_copy);
			if (val_copy)
				free(val_copy);
			free(new);
			new = NULL;
		}
	}
	return (new);
}

/*
**	hash()
**	Uses the 'XOR' version of the djb2 hash.
**	https://softwareengineering.stackexchange.com/questions/49550/
**
**	Certainly, not the *best*, but it's easy to implement...
**
**	I also remap the hash result to the size of our hashmap
**	(this will lead to more collisions, but our hashmap will use
**	less memory... tradeoffs...)
*/

unsigned long	djb2_hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while (c = *str++)
		hash = ((hash << 5) + hash) ^ c;
	return (hash % HASHMAP_SIZE)
}

t_hash_node 	*get_hash_node(t_hash_node hashmap[HASHMAP_SIZE])
{

}

/*
** add_hash_node()
** Checks to see if a t_hash_node with a given key already exists, adds it if
** it's not in the linked list.
*/

int				*add_hash_node(t_hash_node *hashmap, char *key,
				char *value)
{
	t_hash_node	*new;

	if (!get_hash_node(hashmap, key))
	{
		new = new_hash_node(key, value);
		if (hashmap)
		{
			while (hashmap->next)
				hashmap = hashmap->next;
			hashmap->next = new;
			return (1);
		}
		else

	}
	else
		return (0);
}

char			*get_hash_value(t_hash_node *node)
{
	return (node->val);
}
