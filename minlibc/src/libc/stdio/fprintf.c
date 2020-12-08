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

static char _dbuf[_NSSIZ];

void 
fprintf(FILE * restrict stream, char * restrict fmt, ...)
{
    const char dig[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };
    va_list ap;
    long int d = 0;
    char c;
    char *s;
    int n = 0;
    int f = 0;
    int b = 0;
    char item = 0;
    int i;
    char m = 0;
    
    va_start(ap, fmt);
    while (*fmt) {
        c = *fmt++;
        if (!item) {
            if (c == '%') {
                f = 0;
                n = 0;
                item = 1;
            } else
                fputc(c, stream);
        }
        else {
            switch(c) {
            case 's':
                s = va_arg(ap, char *);
                fputs(s, stream);
                item = 0;
            break;

            case 'c':
                c = va_arg(ap, int);
                fputc(c, stream);
                item = 0;
                break;


            case '%':
                fputc('%', stream);
                item = 0;
                break;

            case 'l':
                /*
                 * for compatibility only, due to apparent bug in AVR GCC, 
                 * the actual implementation didn't work and had to be deleted.
                 */
                break;

            case '+':
                f |= _NPLUS;
                break;

            default:
                if (c <= '9' && c >= '0') {   
                    if (n == 0 && c == '0')
                        f |= _NZERO;
                    else
                        n = n * 10 + (c - '0');
                    break;
                }
                switch (c) {
                case 'd':
                    f |= _NSIGN;
                    /* FALLTHROUGH */
                    
                case 'u':
                    b = 10;
                    break;

                case 'o':
                    b = 8;
                    break;

                case 'X':
                    b = 16;
                    break;

                default:
                    panic("bad or unsupported format string");
                }
                
                d = (long int) va_arg(ap, long int);
                _dbuf[_NSSIZ - 1] = 0;
                i = _NSMAX;
                m = '\0';

                if (f & _NSIGN) {
                    if (d < 0) {
                        d = -d;
                        m = '-';
                    }
                    else if (d >= 0 && f & _NPLUS)
                        m = '+';
                }
        
                do {
                    _dbuf[i--] = dig[d % b];
                    d /= b;
                } while (d != 0 && i > 1);

                if (d != 0 && i == 1)
                    panic("digit buffer overflow");

                if (n) {
                    if ((_NSMAX - i) > n)
                        panic("format overflow");

                    if (n > _NSMAX)
                        panic("buffer overflow inevitable");

                    if (f & _NZERO) {
                        for (n -= _NSMAX - i; n > 0; n--)
                            _dbuf[i--] = '0';
                        if (m)
                            _dbuf[i + 1] = m;
                    } else {
                        if (m)
                            _dbuf[i--] = m;
                        for (n -= _NSMAX - i; n > 0; n--)
                            _dbuf[i--] = ' ';
                    }
                }
                else if (m)
                    _dbuf[i--] = m;           
                
                fputs(&_dbuf[i+1], stream);
                item = 0;
       	    }
        }
    }
    va_end(ap);
}
