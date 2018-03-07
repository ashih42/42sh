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

t_hash_node 	*get_hash_node(t_hashmap hmap, char *key)
{
	t_hash_node	*curr;

	if (hmap)
	{
		curr = hmap->nodes[djb2_hash(key)];
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
** add_hash_node()
** Checks to see if a t_hash_node with a given key already exists, adds it if
** it's not in the linked list.
*/

// int				add_hash_node(t_hashmap hmap, char *key, char *value)
// {
// 	t_hash_node	*new;

// 	if (!get_hash_node(hashmap, key))
// 	{
// 		new = new_hash_node(key, value);
// 		if (hashmap)
// 		{
// 			while (hashmap->next)
// 				hashmap = hashmap->next;
// 			hashmap->next = new;
// 			return (1);
// 		}
// 		else

// 	}
// 	else
// 		return (0);
// }

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

int				remove_hash_node(t_hashmap hmap, char *key)
{
	t_hash_node *prev;
	t_hash_node *curr;

	if (hmap)
	{
		prev = NULL;
		curr = hmap->nodes[djb2_hash(key)];
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
				curr = NULL;
				return (0);
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}
