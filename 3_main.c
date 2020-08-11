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
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
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
		write(pipefd[WRITE_END], argv[1], strlen(argv[1]));
		close(pipefd[WRITE_END]);		  /* Reader will see EOF */
		wait(NULL);				/* Wait for child */
	}
	return (EXIT_SUCCESS);
}
