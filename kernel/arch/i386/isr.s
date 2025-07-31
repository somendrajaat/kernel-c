# isr.S
# This file contains the assembly stubs for the first 32 CPU exceptions.

# This macro creates a stub for an ISR that does NOT push an error code.
.macro ISR_NOERRCODE int_no
.global isr\int_no
isr\int_no:
    cli
    push $0
    push $\int_no
    jmp isr_common_stub
.endm

# This macro creates a stub for an ISR that DOES push an error code.
.macro ISR_ERRCODE int_no
.global isr\int_no
isr\int_no:
    cli
    push $\int_no
    jmp isr_common_stub
.endm

# Create the ISR stubs using the macros.
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE   17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

# This is the common stub that all ISRs jump to.
.global isr_common_stub
isr_common_stub:
    pusha           # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    # --- THE FIX IS HERE ---
    # We must explicitly push the current stack pointer (esp) onto the
    # stack. This value is the pointer to the saved registers, and it
    # becomes the argument to our C function.
    push %esp

    call fault_handler # Call our C-level handler

    # After the C function returns, we must clean up the argument
    # we pushed onto the stack.
    add $4, %esp

    popa            # Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    add $8, %esp    # Cleans up the pushed error code and interrupt number
    sti             # Re-enable interrupts
    iret            # Return from interrupt
