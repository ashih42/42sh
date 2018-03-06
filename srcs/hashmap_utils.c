/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:55:36 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 15:41:13 by nmei             ###   ########.fr       */
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

/*
**	get_hash_node()
**
**	Given a hashmap and a key, return the hashnode that contains the exact same
**	key.
**
**	If get_hash_node() can't find a matching node, it returns NULL
*/

t_hash_node 	*get_hash_node(t_hash_node *hashmap, char *key)
{
	t_hash_node	*curr;

	if (hashmap)
	{
		curr = hashmap[djb2_hash(key)];
		while (curr)
		{
			if (ft_strcmp(curr->key, key) == 0)
				return (curr);
			curr = curr->next;
		}
	}
	return (NULL);
}

/*
**	remove_hash_node()
**
**	Given a hashmap and key, we want to remove (free) the hashnode that
**	contains the corresponding key.
**
**	Our remove node function also needs to check if there are nodes
**	before or after the one we want to remove. If so, we need to do some
**	pointer swapping so that the 'prev' of curr will point to curr's 'next'.
**
**	If a hash node is sucessfully removed then the function returns 0.
**	If a hash node wasn't found or the hashmap is invalid returns 1.
*/

int				remove_hash_node(t_hash_node *hashmap, char *key)
{
	t_hash_node *prev;
	t_hash_node *curr;

	if (hashmap)
	{
		prev = NULL;
		curr = hashmap[djb2_hash(key)];
		while (curr)
		{
			if (ft_strcmp(curr->key, key) == 0)
			{
				if (prev)
					prev->next = curr->next;
				if (curr->key)
					free(curr->key);
				if (curr->val)
					free(curr->val);
				free(curr);
				return (0);
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}