#include "../includes/ft_42sh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
/*
**match pattern ? = one character can equal any characters
** match pattern * = any character at any length.
*/
/*
** if a bracket is used, the range of the search needs to be parsed out.
** this can be a literal range (a-z) or (acgfqw)
** checks s2 for the existance of s2 for existance of *s1 parse parse '[' -> ']' if ']' does not exist compare s1 ** with '['
*/
int		chk_glob_brckts(char c1, char *s2)
{
	int i; // increment for search
	int j; // increment for s2
	char *search; // where the string of characters are being stored after being parsed out of the brackets

	i = 0; // first character of search
	j = 0; // first character of s2 
	while (*(s2 + j) != '\0' && *(s2 + j) != ']') // as long as s2[j] is not null or end bracket
		j++;
	if (*(s2 + j) == '\0') //if j gets to a null char before hitting an end bracket, end function by checking if character in question is in fact a '['. If not, return 0.
	{
		if (c1 == '[')
			return (1);
		return (0);
	}
	if (*(s2 + j) == ']') //if there is no dash, all letters are accounted for.
	{
		search = malloc(sizeof(char) * j); //create an array the size of the number of characters we're looking for.
		search[j] = '\0'; // the end of the array has a null character.
		j = 0; //reset the postion of j to prep for string copying (ADD FUNCTION)
		while (*(s2 + j) != ']') //as long as it isn't an end 
		{	
			*(search + i) = *(s2 + j); //copies the s2 string over to search
			j++;
			i++;
		}
		i = 0; //reset search for the actual search
		while (*(search + i) != '\0')//as long as search does not equal null, compare each character to c1. if it fails to find an equal value, return 0.
		{
			if (*(search + i) == c1) // if search + i == c1 return 1
				return (1);
			if (*(search + i) == '-') // if search + i == dash, check range between previous letter and next letter.
			{
				if (c1 >= *(search + i - 1) && c1 <= *(search + i + 1) && *(search + i + 1) != '\0' && *(search + i + 1) != ']' ) //checks all characters between the previous and next letters.
				{
					return (1);
					i = i + 2;
				}
			}
			i++;
		}
	}
	return (0);
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
	while (1)
	{
		if (s1[i] == '\0' && s2[j] == '\0')
			return (0);
		if ((s1[i] == s2[j] && s1[i] != '*' && s1[i] != '\\' && s1[i] != '[') || (s2[j] == '\?'))
		{
			i++;
			j++;
		}
		else if (s1[i] == '\0' && s2[j] == '*')
			j++;
		else if (s1[i] == '\0' || s2[j] == '\0')
			return (1);
		else if (s2[j] == '[') 
		{
			persist =  chk_glob_brckts(s1[i], &s2[j++]);
				if (persist == 1)
				{
					while (s2[j] != ']')
						j++;
					j++;
					i++;
				}
				else 
					return (1);
		}
		else if (s2[j] != '*' && s2[j] != '?' && s2[j] != '[')
			return (1);
		else if (matchparse(&s1[i++], &s2[j + 1]))
			return(0);
	}
}

void	print_list2(t_list *list)
{
	t_list *pointer;

	pointer = list;
	while (pointer)
	{
		ft_printf("%s -> ", pointer);
		pointer = pointer->next;
	}
	ft_printf("X\n");
}

int	list_size(t_list *list)
{
	int i;
	t_list *pointer;

	if (!list)
		return (0);
	i = 0;
	pointer = list;
	while (pointer)
	{
		i++;
		pointer = pointer->next;
	}
	return (i);
}

t_list	*ft_lstdup(t_list *list)
{
	t_list *beginning;
	t_list *pointer;

	pointer = list;
	beginning = 0;
	while (pointer)
	{
		ft_lst_add_last(&beginning, ft_lstnew(pointer->content, pointer->content_size));
		pointer = pointer->next;
	}
	return (beginning);
}

t_list	*get_dir_contents_search(char *dir_path, int ac, char **av)
{
	t_list			*dir_contents;
	t_list			*cache_list;
	t_list			*result;
	DIR				*d;
	struct dirent	*dir;
	char			*temp_path;
	int				i;

	i = 1;
	dir_contents = NULL;
	result = 0;
	if ((d = opendir(dir_path)))
	{
		while ((dir = readdir(d)) && av[i] != '\0')
			if (!ft_strequ(".", dir->d_name) && !ft_strequ("..", dir->d_name))
				ft_lstadd(&dir_contents,
						ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1));
		closedir(d);
	}
	t_list		*pointer;
	while (av[i] != '\0')
	{
		cache_list = ft_lstdup(dir_contents);
		ft_lst_cond_remove(&cache_list, matchparse, av[i], (void (*)(void *, size_t))free);
		pointer = cache_list;
		if (!list_size(pointer))
			ft_lst_add_last(&result, ft_lstnew(av[i], ft_strlen(av[i]) + 1));
		while (pointer)
		{
			ft_lst_add_last(&result, ft_lstnew(pointer->content, pointer->content_size));
			pointer = pointer->next;
		}
		i++;
	}
	return (result);
}
