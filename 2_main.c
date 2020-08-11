#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/**
 * main -  opens a file, & uses its contents as imput for /usr/bin/rev command
 * @argc: Number of arguments
 * @argv: The arguments from the OS command line
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(int argc, char **argv)
{
	char *av[] = {"/usr/bin/rev", NULL};
	int fd;

	(void)argc;
	/* Verify the arguments */
	if (argc < 2)
	{	fprintf(stderr, "Error: Wrong number of arguments\n");
		fprintf(stderr, "Usage: fromfile <file_name>\n");
		return (EXIT_FAILURE);
	}
	/* Open the fileOpen the file for reading "<" */
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{	perror("open");
		return (EXIT_FAILURE);
	}
	/* Duplicate the file on the STDIN stream */
	close(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{	perror("dup2");
		return (EXIT_FAILURE);
	}
	/* Let's try to read something from file */
	if (execve(av[0], av, NULL) == -1)
	{	perror("execve");
		return (EXIT_FAILURE);
	}
	/* Voilà */
	return (EXIT_SUCCESS);
}
