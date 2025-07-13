#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/kernel.h>

void kernel_early_main(void) {
	// Early kernel initialization - runs before C constructors
	// This is where you do critical setup that must happen first
	
	// 1. Initialize terminal for early debugging
	terminal_initialize();
	printf("Early kernel initialization started...\n");
	
	// 2. Set up stack (already done in boot.S, but verify)
	printf("Stack initialized at: %p\n", &kernel_early_main);
	
	// 3. Initialize any critical hardware
	// - CPU features detection
	// - Memory detection
	// - Critical device initialization
	
	// 4. Set up any early memory management
	// - Page tables (if using paging)
	// - Memory regions
	
	// 5. Initialize any early kernel subsystems
	// - Interrupt descriptor table (IDT)
	// - Global descriptor table (GDT) if not done in bootloader
	// - Early device drivers
	
	printf("Early initialization complete.\n");
}

void kernel_main(void) {
	// Main kernel initialization - runs after C++ constructors
	printf("Main kernel initialization started...\n");
	
	// This is where you initialize higher-level subsystems:
	// - File systems
	// - Process management
	// - User interface
	// - Network stack
	// - etc.
	
	printf("Kernel initialization complete.\n");
	
	// Main kernel loop or user interface
	// while(1) {
	// 	// Kernel main loop
	// }
}
