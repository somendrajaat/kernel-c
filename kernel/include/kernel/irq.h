
/*
* irq.h
*
* Header file for our Hardware Interrupt (IRQ) handling.
*/
#ifndef IRQ_H
#define IRQ_H

#include "interrupts.h" // For the 'registers' struct

// Installs the IRQ handlers.
void irq_install(void);

// Installs a custom handler for a given IRQ
void irq_install_handler(int irq, void (*handler)(struct registers *r));

// Uninstalls a custom handler for a given IRQ
void irq_uninstall_handler(int irq);

#endif // IRQ_H
