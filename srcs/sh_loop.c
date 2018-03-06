/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:11:41 by nmei              #+#    #+#             */
/*   Updated: 2018/03/05 16:19:42 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	sh_loop()
**
**	Our shell loop which consists of:
**
**	1) Listening for user input on stdin
**	2) Parsing the input
**	3) Calling the relevant commands specified in the parsed input
*/

void	sh_loop()
{
	while (1)
	{
		sh_listen();
		sh_parse();
		sh_dispatcher();
	}
}


void	sh_listen()
{

}

void	sh_parse()
{

}

void	sh_dispatcher()
{

}