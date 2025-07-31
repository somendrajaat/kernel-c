/*
* multiboot.h
*
* This header file defines the structures for the Multiboot specification,
* which allows our kernel to get information from the bootloader (GRUB).
*/
#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

#define MULTIBOOT_FLAG_MEM     0x001 // Is there a memory map?
#define MULTIBOOT_FLAG_DEVICE  0x002 // Is there boot device info?
#define MULTIBOO_FLAG_CMDLINE  0x004 // Is there a command line?
// ... and so on for other flags

// The main Multiboot information structure.
// The pointer to this is passed in the EBX register.
typedef struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    // ... other fields
} __attribute__((packed)) multiboot_info_t;

// A single entry in the memory map.
typedef struct multiboot_mmap_entry {
    uint32_t size;
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

// Memory map entry types
#define MULTIBOOT_MEMORY_AVAILABLE        1
#define MULTIBOOT_MEMORY_RESERVED         2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS              4
#define MULTIBOOT_MEMORY_BADRAM           5

#endif // MULTIBOOT_H
