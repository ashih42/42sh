/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharpe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 01:14:17 by msharpe           #+#    #+#             */
/*   Updated: 2018/03/07 02:00:46 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** All functions are to go through match parse once they have a conclusion
** this allows multiple wild cards to be used in a single search.
*/
void matchparse (char *s1, char *s2)
{
	if (s2[j] == '*')
		matchstar(s1, s2);
	if (s2[j] == '?')
		matchq(s1, s2);
	if (s2[j] == '[')
	{
		matchbrackparse(s1, s2);
		matchbrack(s1, s2); //another parser is needed for this specfic wildcard.
	}
}
/*
** if a bracket is used, the range of the search needs to be parsed out.
** this can be a literal range (a-z) or (acgfqw).
*/
void matchbrackparse (char *s2)
{


/*
**match pattern [a-z] or [abc] = any character in bracket range is acceptable
*/
int	matchbrack(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (1)
	{
		if (s1[i] == '\0' && s2[j] == '\0')
			return (1);
		if (s1[i] == s2[j] && s1[i] != '*')
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
		else if (matchbrack(&s1[i++], &s2[j + 1]))
			return (1);
	}
}
/*
**match pattern ? = one character can equal any characters
*/
int	matchq(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (1)
	{
		if (s1[i] == '\0' && s2[j] == '\0')
			return (1);
		if (s1[i] == s2[j] && s1[i] != '?')
		{
			i++;
			j++;
		}
		else if (s1[i] == '\0' && s2[j] == '?')
			j++;
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		else if (s2[j] != '?')
			return (0);
		else if (matchq(&s1[i++], &s2[j + 1]))
			return (1);
	}
}
/*
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
		if (s1[i] == '\0' && s2[j] == '\0')
			return (1);
		if (s1[i] == s2[j] && s1[i] != '*')
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