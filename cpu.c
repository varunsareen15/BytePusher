#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

// BytePusher executes 65536 instructions per second (256 per frame at 60fps)
#define INSTRUCTIONS_PER_FRAME 256

CPU* cpu_init(Memory* memory, Display* display, Input* input) {
    if (!memory || !display || !input) {
        return NULL;
    }

    CPU* cpu = (CPU*)malloc(sizeof(CPU));
    if (!cpu) {
        return NULL;
    }

    cpu->memory = memory;
    cpu->display = display;
    cpu->input = input;

    return cpu;
}

void cpu_free(CPU* cpu) {
    if (cpu) {
        free(cpu);
    }
}

void cpu_execute_instruction(CPU* cpu) {
    // Get program counter (24-bit address)
    uint32_t pc = memory_read_address(cpu->memory, MEMORY_ADDR_PC);
    
    // Each instruction is 3 bytes (A, B, C)
    uint8_t A = memory_read_byte(cpu->memory, pc);
    uint8_t B = memory_read_byte(cpu->memory, pc + 1);
    uint8_t C = memory_read_byte(cpu->memory, pc + 2);
    
    // Prepare next PC (PC + 3)
    uint32_t next_pc = (pc + 3) & 0xFFFFFF; // Ensure it stays 24-bit
    
    // Store next PC back to memory
    memory_write_byte(cpu->memory, MEMORY_ADDR_PC, (next_pc >> 16) & 0xFF);
    memory_write_byte(cpu->memory, MEMORY_ADDR_PC + 1, (next_pc >> 8) & 0xFF);
    memory_write_byte(cpu->memory, MEMORY_ADDR_PC + 2, next_pc & 0xFF);
    
    // Perform operation: mem[A*256+B] = mem[C*256+mem[A*256+B]]
    uint16_t addr_AB = (A << 8) | B;
    uint8_t value_AB = memory_read_byte(cpu->memory, addr_AB);
    uint16_t addr_C = (C << 8) | value_AB;
    uint8_t value_C = memory_read_byte(cpu->memory, addr_C);
    
    memory_write_byte(cpu->memory, addr_AB, value_C);
}

void cpu_execute_frame(CPU* cpu) {
    // Execute 256 instructions per frame (at 60 FPS, this is 15360 per second)
    for (int i = 0; i < INSTRUCTIONS_PER_FRAME; i++) {
        cpu_execute_instruction(cpu);
    }
}