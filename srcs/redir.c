#include "ft_42sh.h"

/*
** expr < filename
*/

// int 	redir_input(char **expr, char *filename)
// {
// 	int fd;
// 	int pid;

// 	if ((fd = open(filename, O_RDONLY)) < 0)
// 		return (ft_puterror("cannot open file: ", filename, 1));
// 	if ((pid = fork()) < 0)
// 		return (ft_puterror("fork() failed", 0, 1));
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		exit(execvp(expr[0], expr));
// 	}
// 	wait(0);
// 	return (0);
// }

// /*
// ** expr > filename
// */

// int 	redir_output(char **expr, char *filename)
// {
// 	int fd;
// 	int pid;

// 	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
// 		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
// 		return (ft_puterror("cannot open file: ", filename, 1));
// 	if ((pid = fork()) < 0)
// 		return (ft_puterror("fork() failed", 0, 1));
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		exit(execvp(expr[0], expr));
// 	}
// 	wait(0);
// 	return (0);
// }

// /*
// ** expr >> filename
// */

// int 	redir_append(char **expr, char *filename)
// {
// 	int fd;
// 	int pid;

// 	if ((fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
// 		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
// 		return (ft_puterror("cannot open file: ", filename, 1));
// 	if ((pid = fork()) < 0)
// 		return (ft_puterror("fork() failed", 0, 1));
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		exit(execvp(expr[0], expr));
// 	}
// 	wait(0);
// 	return (0);
// }

// /*
// ** expr1 | expr2
// */

// int	pipe_exprs(char **expr1, char **expr2)
// {
// 	int	pid;
// 	int fd[2];

// 	if (pipe(fd) < 0)
// 		return (ft_puterror("pipe() failed", 0, 1));
// 	if ((pid = fork()) < 0)
// 		return (ft_puterror("fork() failed", 0, 1));
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		exit(execvp(expr1[0], expr1));
// 	}
// 	if ((pid = fork()) < 0)
// 		return (ft_puterror("fork() failed", 0, 1));
// 	if (pid == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		exit(execvp(expr2[0], expr2));
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	wait(0);
// 	wait(0);
// 	return (0);
// }


