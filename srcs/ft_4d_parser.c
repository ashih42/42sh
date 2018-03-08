/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:49:13 by apuel             #+#    #+#             */
/*   Updated: 2018/03/08 04:31:04 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	},
**	group
**	{
**		argv{},
**		argv{},
**		argv{},
**		argv{}
**	}
*/

char	****ft_4d_parser(char *input)
{
	char	**groups;
	char	**cmds;
	char	****result;
	size_t	i;
	size_t	j;

	groups = ft_strsplit(input, ';');
	result = ft_memalloc((ft_char_array_length(groups) + 1) * sizeof(char ***));
	i = 0;
	while (groups[i])
	{
		cmds = //a form of ft_strsplit that splits between '|' and '&&' (shouldn't remove '|', leave it at the end of the left string)
		result[i] = ft_memalloc((ft_char_array_length(cmds) + 1) * sizeof(char **));
		j = 0;
		while (cmds[j])
			result[i][j] = split_argv(cmds[j], WHITESPACE);
		ft_char_array_del(cmds);
	}
	ft_char_array_del(groups);
	return (result);
}
