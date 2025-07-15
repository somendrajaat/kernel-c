.global gdt_flush
gdt_flush:
    movl 4(%esp), %eax      # Load pointer to GDT descriptor into eax
    lgdt (%eax)             # Load GDT
    movw $0x10, %ax         # Data segment selector (offset 0x10)
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $next       # Far jump to reload CS (code segment selector)
next:
    ret
