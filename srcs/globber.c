/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharpe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:56:53 by msharpe           #+#    #+#             */
/*   Updated: 2018/03/09 01:29:27 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
/*
**match pattern [a-z] or [abc] = any character in bracket range is acceptable
*/
int	matchbrack(char *s1, char *s2, char *search)
{
	size_t	i;
	size_t	j;
	size_t	q;
	 
	q = 0;
	i = 0;
	j = 0;
	while (search[q] != '\0')
	{
		if (s1[i] == search[j] && s1[i] != '*')
			return (1);
		else if (search[j] == '\0')
			return (0);
		else if (matchbrack(&s1[i], &search[j++]))
			return (1);
	}
	return (0);
}
/*
**match pattern ? = one character can equal any characters
** match pattern * = any character at any length.
*/
int	matchstar(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (1)
	{
		if (s1[i] == s2[j] && s1[i] != '*' || s1[i] != '\0' && s2[j] == '?')
		{
			i++;
			j++;
		}
		else if (s1[i] == '\0' && s2[j] == '*')
			j++;
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		else if (s2[j] != '*')
			return (0);
		else if (matchstar(&s1[i++], &s2[j + 1]))
			return (1);
	}
}
/*
** if a bracket is used, the range of the search needs to be parsed out.
** this can be a literal range (a-z) or (acgfqw).
*/
void matchbrackparse (char *s1, char *s2)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	char *search;
	while (s2[j] != ']')
		j++;
	search = malloc(sizeof(char) * i);
	search[i] = '\0';
	while (s2[j++] != ']')
	{
		search[q] == s2[j];
		q++;
	}
	persist = matchbrack(s1, s2, search);
}
/*
** All functions are to go through match parse once they have a conclusion
** this allows multiple wild cards to be used in a single search.
*/
int matchparse (char *s1, char *s2)
{
	int persist;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	persist = 0;
	while(1)
	{
		if (s1[i] == '\0' && s2[j] == '\0')
			return (1);
		if (s1[i] == '\0' || s2[j] == '\0')
			return (0);
		s2[j] == '*' || s2[j] == '?' ? persist = matchstar(s1, s2) : 0;
		if (s2[j] == '[') 
		{
			matchbrackparse(s2): 0;
			persist = matchbrack(s1, s2); //another parser is needed for this specfic wildcard.
		}
		if (persist = 1)
			matchparse(&s1[i++], &s2[j + 1]);
	}
	if (persist = 1)
		matchparse(&s1[i++], &s2[j + 1]);
}

