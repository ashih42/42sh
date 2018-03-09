#include "ft_42sh.h"

/*
** Find the active job with the indicated pgid.
*/

t_job			*find_job(pid_t pgid)
{
	job *j;

	while (j)
	{
		j = j->next;
		if (j->pgid == pgid)
			return (j);
	}
	return (NULL);
}

/*
** Return true if all processes in the job have stopped or completed.
*/

bool			job_is_stopped(t_job *j)
{
	process		*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

/*
** Return true if all processes in the job have completed.
*/

bool			job_is_completed(t_job *j)
{
	process		*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
