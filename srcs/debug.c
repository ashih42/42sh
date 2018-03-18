/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 03:32:45 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:19:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	print_list(t_list *list)
{
	ft_printf("  list size = %d\n", ft_lst_size(list));
	ft_printf("  BEGIN\n");
	while (list != 0)
	{
		ft_printf("    %s\n", list->content);
		list = list->next;
	}
	ft_printf("  END\n");
}

void	print_expr_list(t_list *expr_list)
{
	int		i;
	char	**array;

	ft_printf("expr_list size = %d\n", ft_lst_size(expr_list));
	while (expr_list != 0)
	{
		ft_printf("Next expr:\n");
		array = expr_list->content;
		i = -1;
		while (array[++i])
			ft_printf("   %s\n", array[i]);
		expr_list = expr_list->next;
	}
}

void	print_char2d(char **array)
{
	int i;

	ft_printf("    array_2d:\n");
	i = -1;
	while (array[++i])
	{
		ft_printf("      %s ", array[i]);
	}
	ft_printf("\n");
}

void	print_char4d(char ****array)
{
	int		i;
	int		j;
	char	***array_3d;

	i = -1;
	while (array[++i])
	{
		ft_printf("array_4d:\n");
		array_3d = array[i];
		j = -1;
		while (array_3d[++j])
		{
			ft_printf("  array_3d:\n");
			print_char2d(array_3d[j]);
		}
	}
}
