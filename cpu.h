#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"
#include "display.h"
#include "input.h"

typedef struct {
    Memory* memory;
    Display* display;
    Input* input;
} CPU;

// Initialize CPU
CPU* cpu_init(Memory* memory, Display* display, Input* input);

// Free CPU
void cpu_free(CPU* cpu);

// Execute one instruction
void cpu_execute_instruction(CPU* cpu);

// Execute one frame (256 instructions per frame)
void cpu_execute_frame(CPU* cpu);

#endif // CPU_H
