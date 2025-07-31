/*
* heap.h
*
* Header file for the kernel's dynamic memory allocator (heap).
* This implements a simple version of malloc and free.
*/
#ifndef HEAP_H
#define HEAP_H

#include <stddef.h> // For size_t

// The structure that sits at the beginning of every memory block.
typedef struct block_meta {
    size_t size;           // The size of the data area of the block.
    int is_free;           // Flag to check if the block is currently free.
    struct block_meta *next; // Pointer to the next block in the linked list.
} block_meta_t;

// Initializes the heap. Needs to be called once before using malloc.
// `heap_start_addr` should be an address from your PMM that is page-aligned.
// `heap_size` is the total size of the memory region for the heap.
void heap_install(void* heap_start_addr, size_t heap_size);

// Allocates a block of memory of at least `size` bytes.
void *kmalloc(size_t size);

// Frees a previously allocated block of memory.
void kfree(void *ptr);

#endif // HEAP_H
