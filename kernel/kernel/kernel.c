#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/vga_debug.h>
#include <kernel/gdt.h>
#include <kernel/keyboard.h>
#include <kernel/multiboot.h>
#include<kernel/pmm.h>
#include<kernel/heap.h>



void kernel_early_main(multiboot_info_t* mbi) {
 
    gdt_install();
    
    terminal_initialize();
    print_memory_map(mbi);

    printf("TTY driver initialized.\n");

    idt_install();
    printf("IDT and ISRs installed.\n");

    irq_install();
    printf("IRQs remapped and installed.\n");


    keyboard_install();
    printf("Keyboard  installed.\n");

  
    // asm volatile ("sti");
    printf("Interrupts enabled.\n");

    printf("Early initialization complete.\n");
}

void kernel_main(void) {
    printf("\nKernel main has been reached.\n");
    printf("You can now test interrupts.\n\n");
    printf("\n heap starting \n");
    heap_install((void*)0x100000, 0x7ee0000);
    


    //-------------------------------------------tests----------------------------------------------------
    //___________________heap test____________________


    printf("\n--- Testing kmalloc and kfree ---\n");

    // 1. Allocate a first block of memory.
    printf("Allocating first block (ptr1)...\n");
    void* ptr1 = kmalloc(100);
    printf("  ptr1 allocated at: 0x%x\n", ptr1);

    // 2. Allocate a second block, just to make sure the heap moves.
    printf("Allocating second block (ptr2)...\n");
    void* ptr2 = kmalloc(200);
    printf("  ptr2 allocated at: 0x%x\n", ptr2);

    // 3. Now, free the FIRST block.
    printf("Freeing first block (ptr1).\n");
    kfree(ptr1);

    // 4. Allocate a third block of the SAME SIZE as the first one.
    printf("Allocating third block (ptr3) of the same size...\n");
    void* ptr3 = kmalloc(100);
    printf("  ptr3 allocated at: 0x%x\n", ptr3);

    printf("\n--- Verification ---\n");
    if (ptr1 == ptr3) {
        printf("SUCCESS: kfree works! The memory block was reused.\n");
    } else {
        printf("FAILURE: kfree did not work as expected.\n");
    }


    // asm volatile (
        //     "mov $1, %eax\n\t"
        //     "xor %edx, %edx\n\t"
        //     "mov $0, %ecx\n\t"
        //     "div %ecx"
        // );
        
    //-------------------------------------------tests----------------------------------------------------
    
    // for (int j=0;;j++) printf("%d \n",j);
}

