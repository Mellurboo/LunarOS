#include <stdbool.h>
#include <stddef.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xC03FF000;
 
static size_t tty_row;
static size_t tty_column;
static uint8_t tty_color;
static uint16_t* tty_buffer;
 
void tty_initialize(void) {
	tty_row = 0;
	tty_column = 0;
	tty_color = vga_entry_color(COLOR_WHITE, COLOR_CYAN);
	tty_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}

void tty_setcolor(uint8_t color) {
	tty_color = color;
}
 
void tty_entrypoint(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = vga_entry(c, color);
}


void tty_scroll(int line) {
	int loop;
	char c;

	for(loop = line * (VGA_WIDTH * 2) + 0xC03FF000; loop < VGA_WIDTH * 2; loop++) {
		c = loop;
		c = (loop - (VGA_WIDTH * 2));
	}

}

void tty_delete_last_line() {
	int x, *ptr;
 
	for(x = 0; x < VGA_WIDTH * 2; x++) {
		ptr = 0xC03FF000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
		*ptr = 0;				// simply reset it for the next itt of the loop, this confused me at first
	}
}

/// @brief put individual characters, we can utilise this later for longer things and eventually printf (edit: thats done)
/// @param c target char to print
void tty_putchar(char c) {
	int line;
	unsigned char uc = c;

	switch (c)
	{
		case '\n':
		{
			if (c == '\n')
			tty_column = 0;
			tty_row++;
			return;
		}
		break;
	
	default:
		break;
	}
 
	tty_entrypoint(uc, tty_color, tty_column, tty_row);
	if (++tty_column == VGA_WIDTH) {
		tty_column = 0;
		if (++tty_row == VGA_HEIGHT)
		{
			for(line = 1; line <= VGA_HEIGHT - 1; line++)
			{
				tty_scroll(line);
			}
			tty_delete_last_line();
			tty_row = VGA_HEIGHT - 1;
		}
	}
}

// this is my favourite thing possibly ever 
void tty_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		tty_putchar(data[i]);
}
 
void tty_writestring(const char* data) {
	tty_write(data, strlen(data));
}