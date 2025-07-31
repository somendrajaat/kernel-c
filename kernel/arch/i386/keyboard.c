/*
* keyboard.c
*
* Implementation for our PS/2 Keyboard Driver with Shift key support.
*/
#include "kernel/keyboard.h"
#include "kernel/irq.h"
#include "kernel/ports.h"
#include <stdio.h>
#include <stdbool.h> // For bool type


static bool lshift_pressed = false;
static bool rshift_pressed = false;


#define LSHIFT_PRESS   0x2A
#define LSHIFT_RELEASE 0xAA
#define RSHIFT_PRESS   0x36
#define RSHIFT_RELEASE 0xB6


unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*', 0, ' ',
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0, '-', 0,   0,   0, '+', 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0
};


unsigned char kbdus_shift[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
   '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0, '*', 0, ' ',
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0, '-', 0,   0,   0, '+', 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0
};



void keyboard_handler(struct registers *r)
{
    unsigned char scancode;
    scancode = inb(0x60);


    if (scancode == LSHIFT_PRESS) {
        lshift_pressed = true;
        return;
    } else if (scancode == LSHIFT_RELEASE) {
        lshift_pressed = false;
        return;
    } else if (scancode == RSHIFT_PRESS) {
        rshift_pressed = true;
        return;
    } else if (scancode == RSHIFT_RELEASE) {
        rshift_pressed = false;
        return;
    }


    if (scancode & 0x80) {
        
    } else {
        
        char c;
        if (lshift_pressed || rshift_pressed) {
            c = kbdus_shift[scancode];
        } else {
            c = kbdus[scancode];
        }

        if (c) {
            putchar(c);
        }
    }
    (void)r;
}

void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}
