

// #include "pmm.h" // A future pmm.h header
#include "kernel/multiboot.h"
#include <stdio.h>

void print_memory_map(multiboot_info_t* mbi) {
    // Check if the memory map flag is set
    if (!(mbi->flags & MULTIBOOT_FLAG_MEM)) {
        printf("Error: GRUB did not provide a memory map.\n");
        return;
    }

    printf("\nMemory Map provided by GRUB:\n");
    
    uint32_t current_addr = mbi->mmap_addr;
    uint32_t end_addr = mbi->mmap_addr + mbi->mmap_length;

    while (current_addr < end_addr) {
        multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)current_addr;

        printf("  Addr: 0x%x, Len: 0x%x, Type: %d ",
            (uint32_t)mmap->addr, (uint32_t)mmap->len, mmap->type);
        
        switch(mmap->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                printf("(Available RAM)\n");
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                printf("(Reserved)\n");
                break;
            default:
                printf("(Other)\n");
                break;
        }

        current_addr += mmap->size + sizeof(mmap->size);
    }
}
