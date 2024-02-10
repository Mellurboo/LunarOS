#include <kernel/tty.h>
#include <stdio.h>

// simple test to see what the crack is

void kernel_main(void) {
  tty_initialize();
  tty_writestring("Hello from tty_writestring because printf is broken rn");
  printf("col");
  
  // causes the OS to reset. i think its a pagefaut
}
