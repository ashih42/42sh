#include "ft_42sh.h"
#include <sys/types.h>
#include <sys/stat.h>

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

int		is_dir(char *path)
{
	struct stat	s_stat;

	if (stat(path, &s_stat) != 0)
		return (0);
	return (S_ISDIR(s_stat.st_mode));
}
