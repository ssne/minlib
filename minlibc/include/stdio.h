#ifndef _STDIO_H_
#define _STDIO_H_

#include <hal.h>

typedef int size_t;

#ifndef FOPEN_MAX
#define FOPEN_MAX 6
#include <file.h>
FILE _iob[FOPEN_MAX];
int _ioc;
FILE *stdin;
FILE *stdout;
FILE *stderr;
#endif

#ifndef NULL
#define NULL ((void *) 0L)
#endif

#define EOF (-1)
#define CSI "\033[" /* ANSI terminal escape sequence */

int     fputc(int, FILE *);
int     fputs(const char *, FILE *);
int     fgetc(FILE *);
int     fflush(FILE *);
int     fpurge(FILE *);
char    *fgets(char * restrict, int, FILE * restrict);
void    fprintf(FILE * restrict, char * restrict, ...);
void    panic(char *);
size_t  fread(void * restrict, size_t, size_t, FILE * restrict);
size_t  fwrite(const void * restrict, size_t, size_t, FILE * restrict);

#define _NSMAX (_NSSIZ - 2)
enum _nflags {
    _NPLUS = (1 << 0),
    _NZERO = (1 << 2),
    _NSIGN = (1 << 3)
};

#endif
