/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 04:17:36 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:21:30 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	strip_helper(size_t *i, size_t *j, int *quote, char **argv)
{
	while (argv[*i][*j])
	{
		if (!*quote && (argv[*i][*j] == '\"' || argv[*i][*j] == '\''))
		{
			*quote = argv[*i][*j];
			ft_memmove(argv[*i] + *j, argv[*i] + *j + 1,
				ft_strlen(argv[*i] + *j + 1) + 1);
		}
		else if (argv[*i][*j] == *quote)
		{
			*quote = 0;
			ft_memmove(argv[*i] + *j, argv[*i] + *j + 1,
				ft_strlen(argv[*i] + *j + 1) + 1);
		}
		else if (argv[*i][*j] == '\\' && (!*quote || argv[*i][*j + 1] == '\"'
			|| argv[*i][*j + 1] == '\'' || argv[*i][*j + 1] == '$'))
		{
			ft_memmove(argv[*i] + *j, argv[*i] + *j + 1,
				ft_strlen(argv[*i] + *j + 1) + 1);
			if (!argv[*i][++(*j)])
				break ;
		}
		else
			(*j)++;
	}
}

void		strip_argv(char **argv)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	while (argv[++i])
	{
		quote = 0;
		j = 0;
		strip_helper(&i, &j, &quote, argv);
	}
}
