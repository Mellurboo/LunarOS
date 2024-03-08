#include <kernel/tty.h>
#include <stdio.h>

// simple test to see what the crack is

void kernel_main(void) {
  tty_initialize();
  
  printf("LC PRINTF");
  
  // causes the OS to reset. i think its a pagefaut
}
