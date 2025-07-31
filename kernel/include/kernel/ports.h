/*
* ports.h
*
* A simple header for I/O port operations.
* We need this to communicate with the PIC.
*/
#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

// Reads a byte from the specified port.
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// Writes a byte to the specified port.
static inline void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a"(data), "dN"(port));
}

#endif // PORTS_H
