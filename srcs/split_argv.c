#include "ft_42sh.h"

static int is_ws(char c, char *ws)
{
	int i;

	i = 0;
	while (ws[i])
	{
		if (ws[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_substrings(char const *s, char *ws)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (1)
	{
		while (is_ws(s[i], ws))
			i++;
		if (s[i] == '\0')
			return (count);
		while (!(is_ws(s[i], ws) || s[i] == '\0'))
			i++;
		count++;
	}
}

static void	initialize_strings(char **array, char const *s, char *ws)
{
	int		i;
	int		j;
	int		head;

	i = 0;
	j = 0;
	head = 0;
	while (1)
	{
		while (is_ws(s[i], ws))
			i++;
		if (s[i] == '\0')
		{
			array[j] = 0;
			return ;
		}
		head = i;
		while (!(is_ws(s[i], ws) || s[i] == '\0'))
			i++;
		array[j] = malloc(sizeof(char) * (i - head + 1));
		j++;
	}
}

static void	fill_array(char **array, char const *s, char *ws)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		while (is_ws(s[i], ws))
			i++;
		if (s[i] == '\0')
			return ;
		k = 0;
		while (!(is_ws(s[i], ws) || s[i] == '\0'))
		{
			array[j][k] = s[i];
			k++;
			i++;
		}
		array[j][k] = '\0';
		j++;
	}
}

char		**split_argv(char const *s, char *ws)
{
	char	**total_array;
	int		len;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		total_array = ft_memalloc(sizeof(char *) * 2);
		if (total_array == NULL)
			return (NULL);
		else
		{
			total_array[0] = ft_strnew(0);
			return (total_array);
		}
	}
	len = count_substrings(s, ws);
	if ((total_array = malloc(sizeof(char *) * (len + 1))))
	{
		initialize_strings(total_array, s, ws);
		fill_array(total_array, s, ws);
	}
	return (total_array);
}
