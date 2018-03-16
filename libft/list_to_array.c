/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 04:19:55 by ashih             #+#    #+#             */
/*   Updated: 2018/03/16 04:20:13 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**list_to_array(t_list *list)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * (ft_lst_size(list) + 1));
	i = 0;
	while (list != 0)
	{
		array[i++] = ft_strdup(list->content);
		list = list->next;
	}
	array[i] = 0;
	return (array);
}
