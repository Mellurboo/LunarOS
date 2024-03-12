#include <kernel/tty.h>
#include <kernel/IOAccess.h>
#include <stdio.h>

// simple test to see what the crack is

void kernel_main(void) {
  tty_initialize();
  
  printf("Kernel Main\n");
  printf("Welcome to the Lunar Kernel!");

  shutdown(12021);
}

/// @brief power management of the system.
/// @param type what type of shutdown
void shutdown(int type){
  switch (type)
  {
  case 0:
    outbyte16(0x604, 0x2000);
    break;

  case 1:
    __asm__ ("jmp 0xFFFF"); // TODO implement real reboot using ACPI but for now we can js triple fault the system
    break;
  
  default:
    tty_setcolor(TTY_ERROR);
    printf("\nA shutdown was attempted\nhowever could not be executed due to bad argument");
  }
}