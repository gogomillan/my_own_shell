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

## Tasks

### Task 0. stdout to a file
Write a program that opens a file (in write mode) and redirects stdout to this  
file. Try to print anything on stdout using printf, puts, write, etc and it  
should be printed in the file you opened. You can try to enhance your program  
by passing the file to write in as an argument.  

**Example:**
```Wrap bash
vagrant@trusty-64:~$
vagrant@trusty-64:~$ gcc -Wall -Werror -Wextra -pedantic 0_main.c -o tofile
vagrant@trusty-64:~$ ./tofile
Error: Wrong number of arguments
Usage: tofile <file_name>
vagrant@trusty-64:~$
vagrant@trusty-64:~$ ./tofile algo
vagrant@trusty-64:~$ cat algo
Test on stdout
Holberton School
Cali, CO
vagrant@trusty-64:~$
```

**File:** [0_main.c](0_main.c)

### Task 1. stdout to end of a file
Write a program that opens a file (in write mode) and redirects stdout at the 
end of this file. Try to print anything on stdout using printf, puts, write,  
etc and it should be appended at the end of the file you opened. You can try to  
enhance your program by passing the file to write in as an argument.  

**Example:**
```wrap bash
vagrant@trusty-64:~$
vagrant@trusty-64:~$ gcc -Wall -Werror -Wextra -pedantic 1_main.c -o addfile
vagrant@trusty-64:~$ ./addfile Tulsa
vagrant@trusty-64:~$ cat Tulsa
Test append on stdout
Holberton School
Cali, CO
vagrant@trusty-64:~$ ./addfile Tulsa
vagrant@trusty-64:~$ cat Tulsa
Test append on stdout
Holberton School
Cali, CO
Test append on stdout
Holberton School
Cali, CO
vagrant@trusty-64:~$ ./addfile Tulsa
vagrant@trusty-64:~$ cat Tulsa
Test append on stdout
Holberton School
Cali, CO
Test append on stdout
Holberton School
Cali, CO
Test append on stdout
Holberton School
Cali, CO
vagrant@trusty-64:~$
```

**File:** [1_main.c](1_main.c)

### Task 1. stdout to end of a file
Write a program that opens a file, and executes the command **_/usr/bin/rev_** with  
the files content as input.  

**Example:**
```wrap bash
vagrant@trusty-64:~$
vagrant@trusty-64:~$ gcc -Wall -Wextra -Werror -pedantic 2_main.c -o fromfile
vagrant@trusty-64:~$
vagrant@trusty-64:~$ ./fromfile Tulsa
tuodts no dneppa tseT
loohcS notrebloH
OC ,ilaC
tuodts no dneppa tseT
loohcS notrebloH
OC ,ilaC
tuodts no dneppa tseT
loohcS notrebloH
OC ,ilaC
vagrant@trusty-64:~$
```

**File:** [2_main.c](2_main.c)

## Author
Gonzalo Gomez Millan [Twitter](https://twitter.com/gogomillan) |
[LinkedIn](https://linkedin.com/in/gogomillan)
