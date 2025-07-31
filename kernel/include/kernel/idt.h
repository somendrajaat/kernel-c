/*
* idt.h
*
* This header file defines the structures for the Interrupt Descriptor Table (IDT).
*/

#include <stdint.h> // For standard integer types

// Defines an entry in the IDT.
// This structure is very similar to the GDEntry.
struct idt_entry {
    uint16_t base_low;    // The lower 16 bits of the address to jump to when this interrupt fires.
    uint16_t sel;         // Kernel segment selector.
    uint8_t  always0;     // This must always be zero.
    uint8_t  flags;       // More flags. See documentation.
    uint16_t base_high;   // The upper 16 bits of the address to jump to.
} __attribute__((packed));

// A pointer structure for the IDT.
// This is what we pass to the 'lidt' instruction.
struct idt_ptr {
    uint16_t limit;
    uint32_t base;        // The address of the first element in our idt_entry_t array.
} __attribute__((packed));


// --- Function Declarations ---

// The main function to install the IDT.
void idt_install(void);

// External assembly function to load the IDT register.
// We will create this in a separate assembly file.
extern void idt_flush(uint32_t idt_ptr);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);