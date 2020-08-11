#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/**
 * main -  opens a file (write mode) & redirects stdout at the end of this file
 * @argc: Number of arguments
 * @argv: The arguments from the OS command line
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(int argc, char **argv)
{
	int fd;

	(void)argc;
	if (argc < 2)
	{	fprintf(stderr, "Error: Wrong number of arguments\n");
		fprintf(stderr, "Usage: addfile <file_name>\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_CREAT | O_WRONLY | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{	perror("open");
		return (EXIT_FAILURE);
	}

	close(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{	perror("dup2");
		return (EXIT_FAILURE);
	}

	/* Let's try to print something on stdout */
	write(STDOUT_FILENO, "Test append on stdout\n", 22);
	puts("Holberton School");
	printf("Cali, CO\n");

	return (EXIT_SUCCESS);
}
