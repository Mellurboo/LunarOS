#include <kernel/tty.h>
#include <kernel/IOAccess.h>
#include <stdio.h>
#include <kernel/multiboot.h>

//extern multiboot_info_t *multiboot_info_ptr;

unsigned long translate_address(unsigned long phys_addr) {
    return phys_addr + 0xC0000000; 
}

void kernel_main(uint32_t magic, uint32_t multiboot_info) {
  tty_initialize();
    /*
  if (multiboot_info_ptr != NULL){
    /*
    //unsigned long mmap_addr = multiboot_info_ptr->mmap_addr;
    //unsigned long mmap_length = multiboot_info_ptr->mmap_length;
    printf("Memory Map:\n");

    for (unsigned long i = 0; i < mmap_length; i += ((memory_map_t *)(mmap_addr + i))->size + sizeof(((memory_map_t *)(mmap_addr + i))->size)) {
      memory_map_t *entry = (memory_map_t *)(mmap_addr + i);
      printf("Base: 0x%lx%08lx, Length: 0x%lx%08lx, Type: %lu\n",
            entry->base_addr_high, entry->base_addr_low,
            entry->length_high, entry->length_low,
            entry->type);
    }
    
  } else {
    tty_setcolor(TTY_WARNING);
    printf("A multiboot compliant bootloader was not found\n");
    STOP_SYSTEM("MULTIBOOT MAGIC NOT COMPLIANT", "multiboot_info_ptr was null");
  }
  */
}

void STOP_SYSTEM(char info[], char verbose[]){
  tty_setcolor(TTY_ERROR);
  printf("\n:/ a fatal error has occured and Lunar OS could not continue\n");
  printf("heres some info about the error: %s\nAdded info: %s", info, verbose);
  __asm__("cli ; hlt");
}