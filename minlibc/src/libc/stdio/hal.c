/*-
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Copyright (c) 2017-2020, Steven R. S. Snelling
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdarg.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

void 
_sinit(void)
{
    _lock();
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
    UCSRA |= (1 << U2X);
    #else
    UCSRA &= ~(1 << U2X);
    #endif
    UCSRB = (1 << TXEN) |
            (1 << RXEN);

    stdin = &_iob[_ioc++];
    stdin->read = _tty_read;
    stdin->write = NULL;

    stdout = &_iob[_ioc++];
    stdout->read = NULL;
    stdout->write = _tty_write;

    stderr = &_iob[_ioc++];
    stderr->read = NULL;
    stderr->write = _err_write;

    fputs(CSI "2J"
          CSI ";H", stdout);
}

void 
_sstop(void)
{
    panic("nothing else to do");
}

char 
_tty_read(void)
{
    char c;
    
    while (!(UCSRA & (1 << RXC)))
        ;
    c = UDR;
    _tty_write(c);
    return c;
}

void 
_tty_write(char c)
{
    if (c == '\n')
        _tty_write('\r');   
    while (!( UCSRA & (1 << UDRE)))
        ;
    UDR = c;
}

void 
_err_write(char c)
{
    char s[] = CSI "1m" "?" CSI "0m";
    
    if (c)
    {
        s[4] = c;
        fputs(s, stdout);
    }
}

int 
fflush(FILE *stream)
{
    return 0;
}

int 
fpurge(FILE *stream)
{
    return 0;
}

int 
fputc(int c, FILE *stream)
{
    if (stream->write == NULL)
        panic("bad file mode");
    stream->write((char) c);    
    return 0;
}

int 
fgetc(FILE *stream)
{
    if (stream->read == NULL)
        return EOF;
    return stream->read();
}

void 
_lock(void)
{
    cli();
}

void 
_unlock(void)
{
    sei();
}
