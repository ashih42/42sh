/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:33 by nmei              #+#    #+#             */
/*   Updated: 2018/03/07 17:51:42 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	main()
**
**	Our shell loop which consists of:
**
**	1) Listening for user input on stdin
**	2) Parsing the input
**	3) Calling the relevant commands specified in the parsed input
*/

void	print_list(t_list *list)
{
	ft_printf("list size = %d\n", ft_lst_size(list));
	t_list *node = list;
	while (node != 0)
	{
		printf("%s\n", node->content);
		node = node->next;
	}
}

void	print_char_array(char **array)
{
	ft_printf("array len = %d\n", ft_char_array_length(array));
	int i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}


int		main(int argc, char **argv, char **envp)
{
	/*
	char *str = "last last|cat>man";
	char **args = split_argv(str, WHITESPACE);
	print_char_array(args);
	printf("\n");

	char **terms;
	t_list *list = 0;
	print_list(list);
	printf("\n");

	int i = -1;
	while (args[++i])
	{
		ft_printf("i = %d, args[i] = %s\n", i, args[i]);

		terms = str_explode(args[i], DELIM);
		print_char_array(terms);
		printf("\n");


		append_terms(&list, terms);
		print_list(list);
		printf("\n");
	}
	

	char **all_terms = list_to_array(list);

	ft_printf("result:\n");
	ft_printf("len = %d\n", ft_char_array_length(all_terms));
	ft_print_char_array(all_terms);


	*/


	t_env	e;

	g_e = &e;
	signal(SIGINT, ft_ctrl_c);
	ft_bzero(&e, sizeof(t_env));
	sh_init(&e, envp);
	while (1)
	{
		sh_listen(&e);
		if (!e.buffer)
			break ;
		argv = sh_parse(&e);
		if (argv)
			sh_dispatcher(&e, ft_char_array_length(argv), argv);
		// NOTE: reusing the argv from main()... what if sh_parse() returns a much longer char **,
		// longer than the amount of memory allocated for the original main()'s argv?

		// To be safe, we should add argc and argv as elements inside t_env e;
	}

	return (0);
}
