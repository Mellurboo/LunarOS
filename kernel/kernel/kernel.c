#include <stdio.h>
#include <kernel/tty.h>

// simple test to see what the crack is

void kernel_main(void) {
	tty_initialize();
	printf("Lunar boot\n");
	
	tty_setcolor(0x4F);
	printf("All done!");
}