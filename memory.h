#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

// BytePusher has 16 MB of memory (2^24 bytes)
#define MEMORY_SIZE (1 << 24)

// Memory addresses for system variables
#define MEMORY_ADDR_PC 0x000000  // Program counter
#define MEMORY_ADDR_PIXELS 0x000001  // Start of pixel data pointer
#define MEMORY_ADDR_KEYBOARD 0x000004  // Keyboard state

typedef struct {
    uint8_t data[MEMORY_SIZE];
} Memory;

// Initialize memory
Memory* memory_init(void);

// Free memory
void memory_free(Memory* memory);

// Load a ROM file into memory
bool memory_load_rom(Memory* memory, const char* filename);

// Read one byte from memory
uint8_t memory_read_byte(Memory* memory, uint32_t address);

// Write one byte to memory
void memory_write_byte(Memory* memory, uint32_t address, uint8_t value);

// Read 24-bit address from memory
uint32_t memory_read_address(Memory* memory, uint32_t address);

#endif // MEMORY_H