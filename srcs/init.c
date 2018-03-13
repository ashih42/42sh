#include "ft_42sh.h"

/*
**	sh_init()
**
**	This function should read in the default shell environment variables
**	(**envp) and load them into our 42sh environment variable data structure...
**
**	Essentially deserialize envp.
*/

void				sh_init(t_env *e, char **envp)
{
	char			*tmp_key;
	char			*tmp_val;
	char			*eq_ptr;

//	job_control(e);
	while (*envp)
		if ((eq_ptr = ft_strchr(*envp, '=')))
		{
			if ((tmp_key = ft_strsub(*envp, 0, eq_ptr - (*envp))) &&
					(tmp_val = ft_strdup(eq_ptr + 1)))
			{
				set_variable(e, tmp_key, tmp_val);
				free(tmp_val);
				free(tmp_key);
			}
			envp++;
		}
	tmp_val = getcwd(NULL, 0);
	set_variable(e, "PWD", tmp_val);
	if (!get_variable(e, "OLDPWD"))
		set_variable(e, "OLDPWD", tmp_val);
	free(tmp_val);
}
