#include "ft_42sh.h"

static int is_delim(char c, char *delim)
{
	int i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_substrings(char const *s, char *delim)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (1)
	{
		while (is_delim(s[i], delim))
			i++;
		if (s[i] == '\0')
			return (count * 2 - 1);
		while (!(is_delim(s[i], delim) || s[i] == '\0'))
			i++;
		count++;
	}
}

static void	initialize_strings(char **array, char const *s, char *delim)
{
	int		i;
	int		j;
	int		head;

	i = 0;
	j = 0;
	head = 0;
	while (1)
	{
		while (is_delim(s[i], delim))
			i++;
		if (s[i] == '\0')
		{
			array[j] = 0;
			return ;
		}
		head = i;
		while (!(is_delim(s[i], delim) || s[i] == '\0'))
			i++;
		array[j++] = malloc(sizeof(char) * (i - head + 1));
		array[j++] = malloc(sizeof(char) * 2);
	}
}

static void	fill_array(char **array, char const *s, char *delim)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		while (is_delim(s[i], delim))
			i++;
		if (s[i] == '\0')
			return ;
		k = 0;
		while (!(is_delim(s[i], delim) || s[i] == '\0'))
		{
			array[j][k] = s[i];
			k++;
			i++;
		}
		array[j++][k] = '\0';
		array[j][0] = s[i++];
		array[j++][1] = '\0';
	}
}

char		**str_explode(char const *s, char *delim)
{
	char	**total_array;
	int		len;

	if (s == NULL)
		return (NULL);
	
	len = count_substrings(s, delim);
	if (len <= 1)
	{
		total_array = ft_memalloc(sizeof(char *) * 2);
		if (total_array == NULL)
			return (NULL);
		else
		{
			total_array[0] = ft_strdup(s);
			return (total_array);
		}
	}

//	ft_printf("len = %d\n", len);
	if ((total_array = malloc(sizeof(char *) * (len + 1))))
	{
//		ft_printf("GOT HERE 1\n");
		initialize_strings(total_array, s, delim);
//		ft_printf("GOT HERE 2\n");
		fill_array(total_array, s, delim);
//		ft_printf("GOT HERE 3\n");
	}
	return (total_array);
}
