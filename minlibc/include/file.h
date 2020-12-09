#ifndef _FILE_H_
#define _FILE_H_

typedef volatile struct {   
    char (*read)(void);
    void (*write)(char);
    size_t bsiz;            /* Normal block size */    
} FILE;

#endif
