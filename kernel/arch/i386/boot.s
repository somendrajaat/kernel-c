# 0 "arch/i386/boot.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "arch/i386/boot.S"
# Declare constants for the multiboot header.
.set ALIGN, 1<<0 # align loaded modules on page boundaries
.set MEMINFO, 1<<1 # provide memory map
.set FLAGS, ALIGN | MEMINFO # this is the Multiboot 'flag' field
.set MAGIC, 0x1BADB002 # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
    # CRITICAL: Disable interrupts FIRST.
    cli
    # Set up the stack so we can call C functions.
    movl $stack_top, %esp
    push %ebx

    call kernel_early_main

    # Call the global constructors.
    call _init

    # Transfer control to the main kernel.
    call kernel_main

    # CRITICAL: Enable interrupts LAST, only after everything is set up.
    # Now the CPU can safely handle hardware events.
    sti

    # Hang if kernel_main unexpectedly returns.
1: hlt
    jmp 1b
.size _start, . - _start
