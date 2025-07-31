/*
* interrupts.h
*
* This header file defines the C-level interrupt handler.
*/

#include <stdint.h>

// A struct defining the register layout when pushed by the 'pusha' instruction.
struct registers {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Pushed by our ISR stubs.
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
};

// The C-level interrupt handler.
void fault_handler(struct registers *regs);