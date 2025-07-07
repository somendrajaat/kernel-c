# === Paths ===
CROSS_PREFIX = i686-elf
CC  = $(CROSS_PREFIX)-gcc
AS  = $(CROSS_PREFIX)-as
LD  = $(CROSS_PREFIX)-ld
GRUB_FILE = grub-file

# === Files ===
ISO_NAME = myos.iso
BIN_NAME = myos.bin
BUILD_DIR = build
ISO_DIR = isodir
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

# === Sources ===
KERNEL_SRC = kernel.c
BOOT_SRC   = boot.s
LINKER     = linker.ld
GRUB_CFG   = grub.cfg

# === Objects ===
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
BOOT_OBJ   = $(BUILD_DIR)/boot.o

# === Flags ===
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T $(LINKER) -ffreestanding -O2 -nostdlib -lgcc

# === Targets ===
all: $(ISO_NAME)

# Compile boot.s
$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) $(BOOT_SRC) -o $@

# Compile kernel.c
$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	$(CC) -c $(KERNEL_SRC) -o $@ $(CFLAGS)

# Link kernel
$(BIN_NAME): $(BOOT_OBJ) $(KERNEL_OBJ) $(LINKER)
	$(CC) $(LDFLAGS) -o $@ $(BOOT_OBJ) $(KERNEL_OBJ)

# Check multiboot compliance
check-multiboot: $(BIN_NAME)
	@$(GRUB_FILE) --is-x86-multiboot $(BIN_NAME) && echo "✅ Multiboot confirmed" || echo "❌ Not a valid multiboot kernel"

# ISO directory
$(ISO_NAME): $(BIN_NAME) $(GRUB_CFG)
	mkdir -p $(GRUB_DIR)
	cp $(BIN_NAME) $(BOOT_DIR)/
	cp $(GRUB_CFG) $(GRUB_DIR)/
	grub-mkrescue -o $(ISO_NAME) $(ISO_DIR)

# Create build dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run in QEMU
run: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_NAME) $(ISO_NAME) $(ISO_DIR)/boot/myos.bin

.PHONY: all clean run check-multiboot
