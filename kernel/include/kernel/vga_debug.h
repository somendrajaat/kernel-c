/*
* vga_debug.h
*
* A simple debugging tool to change the VGA screen color.
* This helps verify code execution without relying on TTY functions.
*/

#include <stdint.h>

extern volatile uint16_t* vga_buffer;
extern const int VGA_COLS;
extern const int VGA_ROWS;

// VGA color codes
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    // ... and so on
};

// Sets the background color of the entire screen.
// This is a very reliable way to confirm a piece of code has run.
void screen_set_background_color(enum vga_color color);
