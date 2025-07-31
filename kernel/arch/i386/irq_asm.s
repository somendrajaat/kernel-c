# irq.S
# This file contains the assembly stubs for the 16 hardware interrupts (IRQs).

# This macro creates a stub for an IRQ.
.macro IRQ int_no, irq_no
.global irq\irq_no
irq\irq_no:
    cli
    push $0             # Push a dummy error code
    push $\int_no       # Push the interrupt number (32 + irq_no)
    jmp irq_common_stub
.endm

# Create the IRQ stubs
IRQ 32, 0
IRQ 33, 1
IRQ 34, 2
IRQ 35, 3
IRQ 36, 4
IRQ 37, 5
IRQ 38, 6
IRQ 39, 7
IRQ 40, 8
IRQ 41, 9
IRQ 42, 10
IRQ 43, 11
IRQ 44, 12
IRQ 45, 13
IRQ 46, 14
IRQ 47, 15

# This is the common stub that all IRQs jump to.
.global irq_common_stub
irq_common_stub:
    pusha           # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    # --- THE FIX IS HERE ---
    # We must explicitly push the current stack pointer (esp) onto the
    # stack. This value is the pointer to the saved registers, and it
    # becomes the argument to our C function 'irq_handler'.
    push %esp

    call irq_handler # Call our C-level handler

    # After the C function returns, we must clean up the argument
    # we pushed onto the stack.
    add $4, %esp

    popa            # Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    add $8, %esp    # Cleans up the pushed error code and interrupt number
    sti             # Re-enable interrupts
    iret            # Return from interrupt
