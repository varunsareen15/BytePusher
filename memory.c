#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

Memory* memory_init(void) {
    Memory* memory = (Memory*)malloc(sizeof(Memory));
    if (!memory) {
        return NULL;
    }

    // Initialize memory to zero
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory->data[i] = 0;
    }

    return memory;
}

void memory_free(Memory* memory) {
    if (memory) {
        free(memory);
    }
}

bool memory_load_rom(Memory* memory, const char* filename) {
    if (!memory || !filename) {
        return false;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return false;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Make sure ROM isn't larger than memory
    if (filesize > MEMORY_SIZE) {
        filesize = MEMORY_SIZE;
    }

    // Load ROM into memory
    size_t bytes_read = fread(memory->data, 1, filesize, file);
    fclose(file);

    // Convert filesize to size_t for comparison to avoid sign mismatch
    return bytes_read == (size_t)filesize;
}

uint8_t memory_read_byte(Memory* memory, uint32_t address) {
    // Ensure address is within bounds
    address &= (MEMORY_SIZE - 1);
    return memory->data[address];
}

void memory_write_byte(Memory* memory, uint32_t address, uint8_t value) {
    // Ensure address is within bounds
    address &= (MEMORY_SIZE - 1);
    memory->data[address] = value;
}

uint32_t memory_read_address(Memory* memory, uint32_t address) {
    // Read 24-bit address (3 bytes)
    uint32_t value = 0;
    value |= memory_read_byte(memory, address) << 16;
    value |= memory_read_byte(memory, address + 1) << 8;
    value |= memory_read_byte(memory, address + 2);
    return value;
}