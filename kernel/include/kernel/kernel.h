#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H
#include "kernel/multiboot.h"
void kernel_early_main(multiboot_info_t* mbi);
void kernel_main(void);

#endif 