// vga_debug.c

#include "kernel/vga_debug.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

void screen_set_background_color(enum vga_color color) {
    for (int row = 0; row < VGA_ROWS; row++) {
        for (int col = 0; col < VGA_COLS; col++) {
            const int index = row * VGA_COLS + col;
            uint8_t existing_char = vga_buffer[index] & 0xFF;
            uint8_t foreground = VGA_COLOR_LIGHT_GREY;
            uint8_t background = color;
            uint8_t color_attribute = (background << 4) | foreground;
            vga_buffer[index] = (uint16_t)color_attribute << 8 | existing_char;
        }
    }
}