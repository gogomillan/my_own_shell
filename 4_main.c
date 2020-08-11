#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END    0
#define WRITE_END   1

/**
 * main - pipes stdout from the /bin/ls to the /usr/bin/rev
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int pipefd[2], status;
	pid_t cpid1, cpid2;
	char *av1[] = {"/usr/bin/rev", NULL};
	char *av2[] = {"/bin/ls", NULL};

	/* Create the pipe */
	if (pipe(pipefd) == -1)
	{	perror("pipe");
		return (EXIT_FAILURE);
	}
	/* Create the first child process for rev */
	cpid1 = fork();
	if (cpid1 == -1)
	{	perror("fork");
		return (EXIT_FAILURE);
	}
	if (cpid1 == 0)				 /* First child reads from pipe */
	{
		close(pipefd[WRITE_END]);		/* Close unused write end */
		close(STDIN_FILENO);			/* Close STDIN for dup */
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
		{	perror("dup2");
			return (EXIT_FAILURE);
		}
		close(pipefd[READ_END]);		/* Close unused read end */
		if (execve(av1[0], av1, NULL) == -1)	/* child exec rev */
		{	perror("execve");
			return (EXIT_FAILURE);
		}
	}
	else						/* Parent process */
	{
		cpid2 = fork();				/* Second child for the ls */
		if (cpid2 == -1)
		{	perror("fork");
			return (EXIT_FAILURE);
		}
		if (cpid2 == 0)
		{
			close(pipefd[READ_END]);		/* Close unused read end */
			close(STDOUT_FILENO);			/* Close the STDOUT for dup */
			if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
			{	perror("dup2");
				return (EXIT_FAILURE);
			}
			close(pipefd[WRITE_END]);		/* Close unused write end */
			if (execve(av2[0], av2, NULL) == -1)	/* child exec ls */
			{	perror("execve");
				return (EXIT_FAILURE);
			}
		}
		else					/* Parent process */
		{
			/* Wait for second child, ls, the producer */
			wait(&status);
			/* Close both sides of pipe to release the consumer process */
			close(pipefd[READ_END]);
			close(pipefd[WRITE_END]);
			/* Wait for the first child, red, the consumer*/
			wait(&status);
			return (EXIT_SUCCESS);
		}
	}
	/* Voilà */
	return (EXIT_SUCCESS);
}
