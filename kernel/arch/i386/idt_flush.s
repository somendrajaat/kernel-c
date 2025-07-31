# idt_flush.S
# Contains the assembly routine to load the Interrupt Descriptor Table.

.global idt_flush   # Make this visible to the linker
.type idt_flush, @function

idt_flush:
    movl 4(%esp), %eax      # Load pointer to IDT descriptor into eax
    lidt (%eax)             # Load IDT
    ret
