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
t_job			*launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			infile
	int			outfile;

	infile = STDIN_FILENO;
	for (p = j->first_process; p; p = p->next)
	{
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				perror("pipe");
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		pid = fork ();
		if (pid == 0)
			launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
		else if (pid < 0)
		{
			perror ("fork");
			exit(1);
		}
		else
		{
			p->pid = pid;
			if (shell_is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
	}
	format_job_info(j, "launched");
	if (!shell_is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
}
*/

t_process		*process_new(char **argv)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	process->next = 0;
	return (process);
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
