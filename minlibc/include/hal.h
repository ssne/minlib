#ifndef _HAL_H_
#define _HAL_H_

#define _NSSIZ 20 /* Length of the buffer that fprintf() uses for numbers */

void _sinit(void) __attribute__ ((naked)) __attribute__ ((section (".init8")));
void _sstop(void) __attribute__ ((naked)) __attribute__ ((section (".fini1")));

void _err_write(char);
void _tty_write(char);
char _tty_read(void);

void _unlock(void);
void _lock(void);

#endif
