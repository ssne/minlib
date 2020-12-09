# Standard C Library implementation example
This library implements a subset of standard C library functions, namely `fprintf()`, `fputs()`, `fgets()`, `fgetc()`, `fputc()`, `fread()`, `fwrite()`, `fflush()`, and also the `fpurge()` function, the last two being non-functional stubs in this version. The library as it is allows one to connect an AVR microcontoller to a VT-100 (ANSI) terminal or a terminal emulator via UART port and exchange data using familiar C functions.

The library is a simplified form of the library that the author had written for AVR in 2017-2018 and reuses some of its functions. The original library was intended for industrial applications and featured a more sophisticated, interrupt-driven IO system with circular buffers, was thoroughly tested and written to be failsafe.

The purpose of both libraries was to provide a drop-in replacement for the standard C library in order to allow vigorous testing of most of the firmware (e.g. interface and the DSP parts) using test benches and Monte-Carlo simulations natively on a workstation.

Although this library is supplied with the hardware abstraction layer for AVR microcontrollers, it can be easily ported to other architectures. The original library had been ported to STM32 and Intel 8032.
