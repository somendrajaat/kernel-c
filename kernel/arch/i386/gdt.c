/*
* gdt.c
*
* This file contains the implementation for setting up the
* Global Descriptor Table (GDT). The GDT is a data structure
* used by the CPU to define memory segments.
*/

// #include "gdt.h" // Your header file
#include <stdint.h>
#include <kernel/gdt.h>

// External assembly function to load the GDT register.
// This is the gdt_flush function you showed earlier.
extern void gdt_flush(uint32_t gdt_ptr);

// Let's declare our GDT with 3 entries, and a GDT pointer
#define GDT_ENTRIES 3
struct gdt_entry gdt_entries[GDT_ENTRIES];
struct gdt_ptr   gdt_ptr;

// Helper function to set the value of one GDT entry.
// This is the core of setting up a segment descriptor.
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    // Set the base address
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    // Set the limit
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    // Set the granularity and access flags
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

// Main function to install the GDT.
void gdt_install(void) {
    // Setup the GDT pointer and limit
    gdt_ptr.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    // 1. The NULL Descriptor (required)
    //    Selector: 0x00
    gdt_set_gate(0, 0, 0, 0, 0);

    // 2. The Code Segment
    //    Selector: 0x08 (index 1 * 8)
    //    Base: 0, Limit: 4GB, Access: Ring 0, Code Segment
    //    Access byte (0x9A):
    //    - Present (1)
    //    - Ring level 0 (00)
    //    - Descriptor type (1) -> Code/Data
    //    - Executable (1) -> Code
    //    - Direction/Conforming (0)
    //    - Readable (1) -> Can be read
    //    - Accessed (0) -> CPU sets this
    //    Granularity byte (0xCF):
    //    - Granularity (1) -> Limit is in 4K blocks
    //    - Size (1) -> 32-bit protected mode
    //    - Long mode (0)
    //    - Available (0)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 3. The Data Segment
    //    Selector: 0x10 (index 2 * 8)
    //    Base: 0, Limit: 4GB, Access: Ring 0, Data Segment
    //    Access byte (0x92):
    //    - Present (1)
    //    - Ring level 0 (00)
    //    - Descriptor type (1) -> Code/Data
    //    - Executable (0) -> Data
    //    - Direction/Conforming (0)
    //    - Writable (1) -> Can be written to
    //    - Accessed (0) -> CPU sets this
    //    Granularity byte (0xCF) is the same as for the code segment.
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Load the GDT
    gdt_flush((uint32_t)&gdt_ptr);
}
