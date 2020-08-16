#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/**
 * main -  Takes the << behaibour
 * @argc: Number of arguments
 * @argv: The arguments from the OS command line
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(int argc, char **argv)
{
	int fd, ret;
	char *buf = NULL, *av[] = {"/usr/bin/rev", NULL};
	size_t len = 0;

	(void)argc;
	/* Verify the arguments */
	if (argc < 2)
	{	fprintf(stderr, "Error: Wrong number of arguments\n");
		fprintf(stderr, "Usage: fromkb MARK\n");
		return (EXIT_FAILURE);
	}
	/* Open the fileOpen the file for tmp */
	fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{	perror("open");
		return (EXIT_FAILURE);
	}
	/* Take the keyboard input */
	do {
		printf("> ");
		ret = getline(&buf, &len, stdin);
		if (ret > 0 && strncmp(buf, argv[1], strlen(buf) - 1) != 0)
			if (write(fd, buf, strlen(buf)) <= 0)
			{	perror("lseek");
				return (EXIT_FAILURE);
			}
	} while (ret > 0 && strncmp(buf, argv[1], strlen(buf) - 1) != 0);
	/* Duplicate the file on the STDIN stream */
	if (lseek(fd, 0, SEEK_SET) == -1)
	{	perror("lseek");
		return (EXIT_FAILURE);
	}
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
