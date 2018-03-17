#include <ft_42sh.h>

size_t        init_parse(char *s1, char *s2)
{
/*
** static int fuck_it ends the call as there is a recursive limit 
** to what's going on. We won't have stack overflows here!
** We don't appreciate you trying to do that either!
*/
    size_t	j;
    char	*str;
    size_t	k;
	int		i;
    static int fuck_it = 1;

    j = 0;
    k = 0;
	ft_printf("\n\n%c", s2[j]);
    while (s2[j] != '\0')
    {
        if  (s2[j] == '{')
        {
			while (s2[k] != '\0')
            {
                k++;
                if (s2[k] == '{')
				{
					ft_printf("We've hit fuck it all.9");
                    fuck_it++;
				}
                if (fuck_it == 5)
                    return (0);
			}
		}
        str = ft_memalloc(k + 1);
		if (!str)
			return (0);	
        while (s2[j] != '}' && s2[j] != '\0')
        {
            while (s2[j] <= ' ' && s2[j] >= '~')
			{
				ft_printf("The cycle continues.10");
				j++;
			}
            while (s2[j] != ',' && s2[j] != '}' && s2[j] != '\0')
            {
				ft_printf("copycat11");
                str[i] = s2[j];
              	i++;
                j++;
            }
			if (s2[j] == ',')
			{
				j++;
				ft_printf("Commas brah.13");
				if (str[0] == '{')
					matchparse(s1, str + 1);
				else
					matchparse(s1, str);
				
			}
			else
			{
				ft_printf("No Commas brah.14");
				if (str[0] == '{')
					matchparse(s1, str + 1);
				else 
					matchparse(s1, str);
			}
			ft_bzero(str, k);
            i = 0;
        }
        ft_printf("get ready to burn it all.12");
		if (s2[j] == '}')
			j++;
       // }
	}
    free(str);
    fuck_it = 0;
	ft_printf("Done!14");
    return (k);
}
