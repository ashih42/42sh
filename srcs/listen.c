#include "ft_42sh.h"

/*
**	sh_listen()
**
**	This function should implement listening on stdin. Will need to read
**	one char at a time so that backspaces and tabs will be supported!!!
**
**	Because the input is of an unspecified length, we will either need to
**	realloc when we are about to go over our allocation limit or use some
**	sort of linked list implementation...
*/

void	sh_listen(t_env *e)
{
	ft_printf("{robot} %s > ", get_variable(e, "PWD"));
	del_and_gnl(STDIN_FILENO, &(e->buffer)); //TODO: read one character at a time to detect tabs :sob:
}
