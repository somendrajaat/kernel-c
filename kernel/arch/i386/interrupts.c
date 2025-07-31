
#include "kernel/interrupts.h" 
#include "kernel/tty.h" 
#include "kernel/vga_debug.h"


const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


void fault_handler(struct registers *regs) {
    printf("reached in fault handler");
    if (regs->int_no < 32) {
        
        terminal_writestring((char*)exception_messages[regs->int_no]);
        terminal_writestring(" Exception. System Halted!\n");
	    


        for (;;);
    }
}
