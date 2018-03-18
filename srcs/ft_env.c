/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 21:56:18 by ashih             #+#    #+#             */
/*   Updated: 2018/03/18 05:22:14 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			ft_env(t_env *e, int argc, char **argv)
{
	t_list	*node;
	char	**content;

	(void)argc;
	(void)argv;
	node = e->envp;
	while (node)
	{
		content = node->content;
		ft_printf("%s=%s\n", content[0], content[1]);
		node = node->next;
	}
	return (0);
}
