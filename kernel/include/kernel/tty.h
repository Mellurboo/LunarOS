#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

#define TTY_DEFAULT 0x9F
#define TTY_ERROR   0X4F

void tty_initialize(void);
void tty_setcolor(uint8_t color);
void tty_putchar(char c);
void tty_write(const char* data, size_t size);
void tty_writestring(const char* data);

#endif
