#include "ft_42sh.h"

t_process		*process_new(t_env *e, char **argv)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	process->next = 0;
	process->argv = argv;
	process->pid = e->child_pid;
	process->completed = 0;
	process->stopped = 0;
	process->completed = 0;
	process->status = 0;
	return (process);
}

void			process_add(t_job *j, t_process *added_process)
{
	t_process *process;

	process = j->first_process;
	if (process)
	{
		while (process && process->next)
			process = process->next;
		process->next = added_process;
	}
	else
		j->first_process = added_process;
}
