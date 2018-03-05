/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:58:05 by apuel             #+#    #+#             */
/*   Updated: 2017/11/27 16:17:24 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void		split_input(char **result, const char *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			result[i] = ft_strnew(word_len(s, c));
			if (result[i])
				while (*s && *s != c)
					result[i][j++] = *s++;
			i++;
		}
		else
			s++;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	num_str;

	if (!s)
		return ((char **)0);
	i = 0;
	num_str = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			i += word_len(&s[i], c);
			num_str++;
		}
		else
			i++;
	}
	result = ft_memalloc(num_str * sizeof(char *));
	if (result)
		split_input(result, s, c);
	return (result);
}
