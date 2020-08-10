# my_own_shell
Workshop for the shell v2 in Holberton School

## Concept
If you need execute a command like next:
```wrap bash
ls > ls_result
```
The previous command will execute ls and redirect stdout to the file named  
ls_result. If a file named ls_result already exists, it will be overwritten. If  
it does not exist, it will be created.  

Our solution is a system call (man 2) named dup2. 

Let's see an example:  
**Example:**
```wrap bash
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - dup2
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(void)
{
    if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        return (EXIT_FAILURE);
    }

    /* Let's try to print something on stdout */
    printf("Test on stdout\n");
    printf("Holberton School\n");
    return (EXIT_SUCCESS);
}
alex@~$ gcc -Wall -Wextra -Werror -pedantic main_0.c
alex@~$ ./a.out
Test on stdout
Holberton School
alex@~$ ./a.out > /dev/null 
Test on stdout
Holberton School
alex@~$ ./a.out 2> /dev/null 
alex@~$
```
Here you can see that what was initially printed on stdout with printf, is now  
printed on stderr. You can check that by redirecting the output on /dev/null,  
and only stderr should remain.  
