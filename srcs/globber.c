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
	int		i; 
	int		j;
	char	*search;

	i = 0;
	j = 0;
	while (*(s2 + j) != '\0' && *(s2 + j) != ']')
		j++;
	if (*(s2 + j) == '\0')
	{
		if (c1 == '[')
			return (1);
		return (0);
	}
	if (*(s2 + j) == ']')
	{
		search = malloc(sizeof(char) * j + 1);
		search[j] = '\0';
		j = 0; 
		while (*(s2 + j) != ']' && *(s2 + j) != '}') //as long as it isn't an end 
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

// while (s2[j] != '}')
// {
// 	while (s2[j] != ',' && s2[j] != '}')
// 	{
// 		search = malloc(sizeof(char) * j + 1);
// 		search[j] = '\0';
// 		j = 0;
// 		while (*(s2 + j) != '}')
// 		{
// 			*(search + i) = *(s2 + j);
// 			j++;
// 			i++;
// 		}
// 		i = 0;
// 		while (*(search + i) != '}')
// 		{
// 			if (*(search + i) == c1)
// 				return (1);
// 			if (*(search + i) == ',')
// 			{
// 				//if
// 			} 
// 		j++;
// 	}
// 	j++;
// }
/*
** All functions are to go through match parse once they have a conclusion
** this allows multiple wild cards to be used in a single search.
*/
int matchparse (char *s1, char *s2)
{
	int		persist;
	size_t	i;
	size_t	j;

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
		else if (s2[j] == '[' || s2[j] == '{') 
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
		else if (s2[j] != '*' && s2[j] != '?' && s2[j] != '[' && s2[j] != '{')
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
	int		i;
	t_list	*pointer;

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
	t_list	*beginning;
	t_list	*pointer;

	pointer = list;
	beginning = 0;
	while (pointer)
	{
		ft_lst_add_last(&beginning, ft_lstnew(pointer->content, pointer->content_size));
		pointer = pointer->next;
	}
	return (beginning);
}

char	*get_basename(char *str)
{
	char	*pointer;

	while (ft_strchr(str, '/'))
		pointer = ft_strchr(str, '/');
	*(++pointer) = '\0';
	return (pointer);
}

bool				populate_nested_path(char *pathname, t_list **list, char *query)
{
	char			*pointer;
	DIR				*d;
	struct dirent	*dir;
	char			*fullpath;

	pointer = pathname;
	*list = NULL;
	while (*pointer)
		pointer++;
	while (*pointer != '/')
		pointer--;
	*(++pointer) = '\0';
	if ((d = opendir(pathname)))
	{
		while ((dir = readdir(d)))
		{
			fullpath = ft_strjoin(pathname, dir->d_name);
			if (!ft_strequ(".", dir->d_name) && !ft_strequ("..", dir->d_name) && matchparse(fullpath, query))
				ft_lst_add_last(list, ft_lstnew(fullpath, ft_strlen(fullpath) + 1));
		}
	}
	return (0);
}

t_list	*get_dir_contents_search(char *dir_path, int ac, char **av)
{
	t_list			*dir_contents;
	t_list			*cache_list;
	t_list			*result;
	DIR				*d;
	struct dirent	*dir;
	int				i;

	(void)ac;
	i = 0;
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
		if (!ft_strchr(av[i], '/'))
			ft_lst_cond_remove(&cache_list, matchparse, av[i], (void (*)(void *, size_t))free);
		else
			populate_nested_path(av[i], &cache_list, av[i]);
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
