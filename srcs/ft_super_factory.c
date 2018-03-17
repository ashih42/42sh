#include "libft/libft.h"

int		find_closing(char *s)
{
	int level = 1;
	int i = ft_strchr(s, '{') - s + 1;

	while (s[i])
	{
//		ft_printf("i=%d, s[i] = %c\n", i, s[i]);
		if (s[i] == '{')
			level++;
		else if (s[i] == '}')
			level--;
		if (level == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char *s, int start, int len)
{
	char *str = ft_strnew(len);
	ft_strncpy(str, s + start, len);
	return (str);
}

void	ft_strtrisect(char *s, char **head, char **tail, char **mid)
{
	int	close;

	close = find_closing(s);
	*head = ft_substr(s, 0, ft_strchr(s, '{') - s);
	*tail = ft_substr(s + close + 1, 0, ft_strlen(s + close + 1));
	*mid = ft_substr(ft_strchr(s, '{') + 1, 0, s + close - ft_strchr(s, '{') - 1);
}

t_list	*split_commas(char *s)
{
	t_list *list;
	char	*head;
	int		brackets;
	char	*str;


	brackets = 0;
	list = 0;
	head = s;
	while (*s)
	{
		if (*s == '{')
			brackets++;
		else if (*s == '}')
			brackets--;
		else if (*s == ',' && brackets == 0)
		{
			str = ft_strnew(s - head);
			ft_strncpy(str, head, s - head);
			ft_lst_add_last(&list, ft_lst_new_ref(str, sizeof(char *)));
			head = s + 1;
		}
		s++;
	}
	str = ft_strnew(s - head);
	ft_strncpy(str, head, s - head);
	ft_lst_add_last(&list, ft_lst_new_ref(str, sizeof(char *)));
	return (list);
}



// no error checking.  assume there are valid matching {}
void	str_factory(char *s, t_list **list)
{
	char	*head;
	char	*mid;
	char	*tail;
//	char	**mid_array;
	t_list	*mid_list;
	t_list	*mid_list_head;
	char	*temp;;
	char	*del;
	int		i;

	ft_strtrisect(s, &head, &tail, &mid);
//	mid_array = ft_strsplit(mid, ',');		// THIS WON'T WORK. WRITE A NEW FUNCTION
	mid_list = split_commas(mid);
	mid_list_head = mid_list;
	while (mid_list)
	{
		temp = ft_strjoin(head, mid_list->content);
		del = temp;
		temp = ft_strjoin(temp, tail);
		ft_lst_add_last(list, ft_lst_new_ref(temp, sizeof(char *)));
		ft_strdel(&del);
		mid_list = mid_list->next;
	}
/*	
	i = -1;
	while (mid_array[++i])
	{
		temp = ft_strjoin(head, mid_array[i]);
		del = temp;
		temp = ft_strjoin(temp, tail);
		ft_lst_add_last(list, ft_lst_new_ref(temp, sizeof(char *)));
		ft_strdel(&del);
	}
*/
	ft_strdel(&head);
	ft_strdel(&mid);
	ft_strdel(&tail);
//	ft_char_array_del(mid_array);
	ft_lstdel(&mid_list_head, (void (*)(void *, size_t))free);
}

// return 1 if every str in list does not contain {}
// return 0 if there are still terms to be factory'd
int		list_is_ready(t_list *list)
{
	char	*str;
	while (list)
	{
		str = list->content;
		if (ft_strchr(str, '{'))
			return (0);
		list = list->next;
	}
	return (1);
}

t_list *super_factory(char *s)
{
	t_list *list = 0;
	t_list *head;
	char	*str;

	ft_lst_add_last(&list, ft_lstnew(s, ft_strlen(s) + 1));
	head = list;
	while (list)
	{
		ft_printf("list->content = %s\n", list->content);
		str = list->content;
		if (ft_strchr(str, '{'))
		{
			str_factory(str, &list);
			ft_strdel(&str);
			list->content = 0;
		}
		list = list->next;
	}
	return (head);
}

void	print_list(t_list *list)
{
	ft_printf("list: ");
	while (list)
	{
		ft_printf("%s, ", list->content);
		list = list->next;
	}
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	
	char *head;
	char *tail;
	char *mid;
//	char str[] = "ft_{a,b}{1,2,3}.c";
//	char str[] = "ft_{a,{1,2}.doop}.c";

//	char str[] = "a{bc{d}e}";
//	ft_printf("find_closing() = %d\n", find_closing(str));
/*
	ft_strtrisect(str, &head, &tail, &mid);
	ft_printf("head = |%s|\n", head);
	ft_printf("mid = |%s|\n", mid);
	ft_printf("tail = |%s|\n", tail);
*/


	

//	char test_str[] = "ft_{a,b}.c";
//	char test_str[] = "ft_{a,b}{1,2,3}.c";
//	char test_str[] = "ft_{a,{1,2}XYZ}.c";
	char test_str[] = "{{a,b}.txt,{c,d}.c}";

//	t_list *list = split_commas(test_str);
	t_list *list = super_factory(test_str);
	ft_printf("list size = %d\n", ft_lst_size(list));
	print_list(list);




	return (0);
}