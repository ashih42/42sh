#include "ft_42sh.h"

t_hash_node		*new_hash_node(char *key, char *val)
{
	t_hash_node *new;
	char		*key_copy;
	char		*val_copy;

	if ((new = (t_hash_node *)malloc(sizeof(t_hash_node))))
	{
		key_copy = ft_strdup(key);
		val_copy = ft_strdup(val);
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
	while ((c = *str++))
		hash = ((hash << 5) + hash) ^ c;
	return (hash % HASHMAP_SIZE);
}

/*
**	get_hash_node()
**
**	Given a hashmap and a key, return the hashnode that contains the exact same
**	key.
**
**	If get_hash_node() can't find a matching node or key is invalid returns NULL
*/

t_hash_node		*get_hash_node(t_hashmap *hmap, char *key)
{
	t_hash_node	*curr;

	if (key)
	{
		curr = (hmap->nodes)[djb2_hash(key)];
		while (curr)
		{
			if (!ft_strcmp(curr->key, key))
				return (curr);
			curr = curr->next;
		}
	}
	return (NULL);
}

/*
**	add_hash_node()
**
**	Checks to see if a t_hash_node with a given key already exists
**	1) If the key node exists, then overwrite the value with our new value
**	2) If the key node does not exist, then create a new node
**
**	If a hash node was successfully added, function returns 0.
**	If a hash node's 'val' was updated, function returns 1.
*/

int				add_hash_node(t_hashmap *hmap, char *key, char *value)
{
	t_hash_node		*prev;
	t_hash_node		*curr;
	unsigned long	hash;

	hash = djb2_hash(key);
	curr = (hmap->nodes)[hash];
	if (curr)
	{
		while (curr)
		{
			if (!ft_strcmp(curr->key, key))
			{
				(curr->val) ? free(curr->val) : 0;
				curr->val = strdup(value);
				return (1);
			}
			prev = curr;
			curr = curr->next;
		}
		prev->next = new_hash_node(key, value);
	}
	else
		(hmap->nodes)[hash] = new_hash_node(key, value);
	return (0);
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
**	If a hash node wasn't found or the key is invalid returns 1.
*/

int				remove_hash_node(t_hashmap *hmap, char *key)
{
	t_hash_node *prev;
	t_hash_node *curr;

	if (key)
	{
		prev = NULL;
		curr = (hmap->nodes)[djb2_hash(key)];
		while (curr)
		{
			if (!ft_strcmp(curr->key, key))
			{
				if (prev)
					prev->next = curr->next;
				(curr->key) ? free(curr->key) : 0;
				(curr->val) ? free(curr->val) : 0;
				free(curr);
				(hmap->nodes)[djb2_hash(key)] = NULL;
				return (0);
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}
