#include "ft_42sh.h"

char	*build_filepath(char *path, char *file)
{
	char	*filepath;

	if ((filepath = ft_strnew(ft_strlen(path) + 1 + ft_strlen(file))))
	{
		ft_strcpy(filepath, path);
		ft_strcat(filepath, "/");
		ft_strcat(filepath, file);
	}
	return (filepath);
}