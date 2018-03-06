/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:55:36 by nmei              #+#    #+#             */
/*   Updated: 2018/03/06 14:15:42 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

t_hash_node	*new_hash_node(char *key, char *val)
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