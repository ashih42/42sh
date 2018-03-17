/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 01:24:38 by nmei              #+#    #+#             */
/*   Updated: 2018/03/17 01:50:56 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	count number of times char 'c' occurs in string s
*/

size_t	ft_count_occurrences(char *s, int c)
{
	size_t	occurrences;

	occurrences = 0;
	while (*s)
	{
		if (*s == c)
			occurrences++;
		s++;
	}
	return (occurrences);
}

/*
**	returns the idx where 'c' first occurs in 's'
**	returns -1 if 'c' never occurs in 's'
*/

ssize_t	ft_fst_occ_idx(char *s, int c)
{
	ssize_t	idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			return (idx);
		idx++;
	}
	return (-1);
}

/*
**	returns the idx where 'c' last occurs in 's'
**	returns -1 if 'c' never occurs in 's'
*/

ssize_t	ft_lst_occ_idx(char *s, int c)
{
	ssize_t	idx;

	idx = ft_strlen(s);
	while (idx > 0)
	{
		if (s[idx] == c)
			return (idx);
		idx--;
	}
	return (-1);
}
