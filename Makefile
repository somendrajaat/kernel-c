.PHONY: all clean

all:
	$(MAKE) -C libc
	$(MAKE) -C kernel
 
clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean