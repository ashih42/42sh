#include "ft_42sh.h"

/*
**	Malloc a job struct.
*/

t_job			*job_new(void)
{
	t_job		*job;

	job = malloc(sizeof(t_job));
	job->next = 0;
	job->command = 0;
	job->first_process = 0;
	job->pgid = getpid();
	job->notified = 0;
	return (job);
}


/*
** Find the active job with the indicated pgid.
*/

t_job			*find_job(pid_t pgid)
{
	t_job		*j;

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
	t_process	*p;

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
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
