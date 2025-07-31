#include "kernel/heap.h"
#include <stddef.h> 

// This will be the head of our linked list of memory blocks.
static block_meta_t *global_heap_base = NULL;


static block_meta_t *find_free_block(block_meta_t **last, size_t size) {
    block_meta_t *current = global_heap_base;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}


void *kmalloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    block_meta_t *block;
    if (!global_heap_base) {
        return NULL;
    } else {
        
        block_meta_t *last = global_heap_base;
        block = find_free_block(&last, size);
        if (!block) {
            
            return NULL;
        }
    }

    
    if ((block->size - size) >= (sizeof(block_meta_t) + 1)) {
        block_meta_t *new_block = (block_meta_t *)((char *)block + sizeof(block_meta_t) + size);
        new_block->size = block->size - size - sizeof(block_meta_t);
        new_block->is_free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }

    block->is_free = 0;

    
    return (void*)(block + 1);
}


static block_meta_t *get_block_ptr(void *ptr) {
    return (block_meta_t*)ptr - 1;
}


void kfree(void *ptr) {
    if (!ptr) {
        return;
    }

    block_meta_t* block_ptr = get_block_ptr(ptr);
    block_ptr->is_free = 1;

    
    block_meta_t *current = global_heap_base;
    while (current) {
        if (current->is_free && current->next && current->next->is_free) {

            current->size += sizeof(block_meta_t) + current->next->size;
            current->next = current->next->next;
            
        } else {
            current = current->next;
        }
    }
}

void heap_install(void* heap_start_addr, size_t heap_size) {
    if (heap_size < sizeof(block_meta_t)) {
        
        global_heap_base = NULL;
        return;
    }

    global_heap_base = (block_meta_t*)heap_start_addr;
    global_heap_base->size = heap_size - sizeof(block_meta_t);
    global_heap_base->is_free = 1;
    global_heap_base->next = NULL;
}
