#include <stdio.h>

/*
 * minlibc example
 *
 * This source is absolutely compatible with UNIX and 
 * standard C in general.
 *
 * You can compile this file with your system compiler,
 * and functionally, you will get the same result.
 */

#define BSIZ 20

int main(void)
{    
    char buf[BSIZ];
    long int i;

    fprintf(stdout, "Hello, world!\n\n");
    
    fputs("Enter some string: ", stdout);
    if (buf != fgets(buf, BSIZ, stdin))
    {
        fprintf(stderr, "\nError: fgets() failed.\n");
        return -1;
    }
    for (i = 0; buf[i]; i++)
        ;
    buf[i - 1] = '\0';
    fprintf(stdout, "You have entered \"%s\"\n"
                    "This string is %ld characters long\n\n", buf, i);
    
    return 0;
}
