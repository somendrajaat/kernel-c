/*
* pmm.h
*
* Header file for the Physical Memory Manager.
*/
#ifndef PMM_H
#define PMM_H

#include "multiboot.h" // We need this for the multiboot_info_t type

// This provides the function prototype for print_memory_map, making it
// visible to other files like kernel.c that include this header.
void print_memory_map(multiboot_info_t* mbi);

// In the future, you will add your PMM functions here, for example:
// void pmm_init(multiboot_info_t* mbi);
// uint32_t pmm_alloc_frame();
// void pmm_free_frame(uint32_t frame);

#endif // PMM_H
