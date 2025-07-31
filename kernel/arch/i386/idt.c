
#include "kernel/idt.h" 

// Declare our IDT with 256 entries.

extern void isr0();

struct idt_entry idt_entries[256];
struct idt_ptr   idt_ptr;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    
    idt_entries[num].flags = flags /* | 0x60 */;
}


void idt_install(void) {
    
    idt_ptr.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    
    for (int i = 0; i < 256; i++) {
        idt_entries[i].base_low = 0;
        idt_entries[i].base_high = 0;
        idt_entries[i].sel = 0;
        idt_entries[i].always0 = 0;
        idt_entries[i].flags = 0;
    }

    
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    

    
    idt_flush((uint32_t)&idt_ptr);
}
