#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END    0
#define WRITE_END   1

/**
 * main - pipes stdout to the command /usr/bin/rev
 * @argc: Arguments counter
 * @argv: Arguments vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char *av[] = {"/usr/bin/rev", NULL};

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}

	if (cpid == 0)				 /* Child reads from pipe */
	{
		close(pipefd[WRITE_END]);		  /* Close unused write end */
		close(STDIN_FILENO);
		/* if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) */
		if (dup(pipefd[READ_END]) == -1)
		{	perror("dup2");
			return (EXIT_FAILURE);
		}

		if (execve(av[0], av, NULL) == -1)
		{	perror("execve");
			return (EXIT_FAILURE);
		}
	}
	else						   /* Parent writes argv[1] to pipe */
	{
		close(pipefd[READ_END]);		  /* Close unused read end */
		close(STDOUT_FILENO);
		/* if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) */
		if (dup(pipefd[WRITE_END]) == -1)
		{	perror("dup2");
			return (EXIT_FAILURE);
		}
		close(pipefd[WRITE_END]);

		printf("]%s[ftp\n", argv[1]);
		fflush(stdout);
		puts(argv[1]);
		fflush(stdout);
		write(STDOUT_FILENO, argv[1], strlen(argv[1]));
		close(STDOUT_FILENO);		  /* Reader will see EOF */
		wait(NULL);				/* Wait for child */
	}
	return (EXIT_SUCCESS);
}
