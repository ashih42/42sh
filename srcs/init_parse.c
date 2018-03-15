#include <ft_42sh.h>

size_t        init_parse(char *s1, char *s2)
{
/*
** static int fuck_it ends the call as there is a recursive limit 
** to what's going on. We won't have stack overflows here!
** We don't appreciate you trying to do that either!
*/
    size_t    j;
    char    *str;
    size_t    k;
	int		 i;
    static int fuck_it = 0;

    j = 0;
    k = 0;
    
    while (s2[j] != '\0')
    {
        if  (s2[j] == '{')
        {
            j++;
            while (s2[j] != '}')
            {
                k++;
                if (s2[j] == '{')
                    fuck_it++;
                if (fuck_it == 5)
                    return (0);
            }
            str = ft_memalloc(k + 1);    
            while (s2[j] != '}')
            {
                while (s2[j] <= ' ' && s2[j] >= '~')
                    j++;
                while (s2[j] != ',' && s2[j] != '}')
                {
                    str[i] = s2[j];
                    i++;
                    j++;
                }
                matchparse(s1, str);
                ft_bzero(str, k);
                i = 0;
                j = j + 2;
            }
            
        }
    }
    free(str);
    fuck_it = 0;
    return (k);
}
