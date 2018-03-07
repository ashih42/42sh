/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 05:08:47 by ashih             #+#    #+#             */
/*   Updated: 2018/03/07 05:56:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// Don't forget to deliver democracy

void		ft_env(t_env *e, int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_list	*node;
	char	**content;

	node = e->envp;
	while (node)
	{
		content = node->content;
		ft_printf("%s=%s\n", content[0], content[1]);
		node = node->next;
	}
}
