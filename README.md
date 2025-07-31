# 🍳 Somendra's Bootleg OS Kernel

> Because writing a simple C program wasn't painful enough.  
> So I made a *bootable OS kernel*. Welcome to pain++, enjoy your stay.

## 🚀 Features (yes, it boots!)

- **Boots via GRUB** (multiboot compliant, I'm not *that* crazy)
- **Sets up GDT & IDT** like a responsible adult
- **Remaps PIC** (because IRQ0 crashing the CPU was getting old)
- **Handles keyboard input** (press keys, watch the magic happen)
- **Prints GRUB memory map** to screen (because `printf` on bare metal is art)
- **Throws interrupts and handles exceptions** like a moody teenager
- **Runs in QEMU** (for now...)

## 🧠 Why?

Because I wanted to understand what happens *before* your main function starts.  
Also, I like debugging weird exceptions with zero OS help.

## 🛠️ How to Run

### Prerequisites

You'll need these tools installed:
- `i686-elf-gcc` (cross-compiler)
- `grub-mkrescue` (GRUB tools)
- `qemu-system-i386` (QEMU emulator)
- `xorriso` (for ISO creation)

### Building and Running

1. **Clone this madness:**
   ```bash
   git clone https://github.com/somendra/os-kernel
   cd os-kernel
   ```

2. **Build it:**
   ```bash
   make
   ```

3. **Run it in QEMU:**
   ```bash
   ./qemu.sh
   ```

   Or if you prefer the manual approach:
   ```bash
   ./build.sh
   ./iso.sh
   qemu-system-i386 -cdrom somendraOS.iso
   ```

**Keyboard input works** — type like a hacker.

## 📸 Screenshot



## 🧪 Current Status

| Feature | Status |
|---------|--------|
| Boots | ✅ Working |
| Interrupts (IRQ) | ✅ Working |
| Keyboard Input | ✅ Working |
| Memory Map Printing | ✅ Working |
| File System | ❌ Not yet |
| Multithreading | ❌ LOL |
| Memory Management | 🚧 Coming Soon (maybe) |

## ⚠️ Warning

This repo contains:
- **Brain-melting C**
- **Assembly code that stares into your soul**
- **Comments that say "TODO: fix this mess"**

Use at your own risk. Especially if you're a sane person.

## 📚 Inspirations

- [OSDev Wiki](https://wiki.osdev.org/)
- Some dude on StackOverflow™
- Pure frustration

---

*Built with ❤️ and a lot of caffeine* 