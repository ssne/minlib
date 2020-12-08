#ifndef _FILE_H_
#define _FILE_H_

typedef volatile struct {   
    char (*read)(void);
    void (*write)(char);
} FILE;

#endif
