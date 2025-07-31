#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/ports.h> // You will need a ports.h for inb/outb

#include "kernel/vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

// --- NEW ---
// Helper function to update the hardware cursor position.
// The VGA controller has two ports, an index port and a data port.
static void update_cursor(void) {
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

// --- NEW ---
// Scrolls the terminal up by one line.
static void terminal_scroll(void) {
    // Move all rows up by one.
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t from_index = y * VGA_WIDTH + x;
            const size_t to_index = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[to_index] = terminal_buffer[from_index];
        }
    }

    // Clear the last line.
    const size_t last_row_index = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[last_row_index + x] = vga_entry(' ', terminal_color);
    }

    // We are now on the last line.
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    update_cursor();
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

// --- UPDATED FUNCTION ---
void terminal_putchar(char c) {
    unsigned char uc = c;

    // Check if we need to scroll
    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
    }

    if (uc == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else if (uc == '\b') {
        if (terminal_column > 0) {
            terminal_column--;
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        } else if (terminal_row > 0) {
            // Handle backspace at the beginning of a line
            terminal_row--;
            terminal_column = VGA_WIDTH - 1;
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        }
    } else {
        terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row++;
        }
    }

    // Check again if we need to scroll after printing
    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
    }

    update_cursor();
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}
