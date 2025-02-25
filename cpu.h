#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MEMORY_SIZE 65536

typedef struct CPU {
	uint8_t memory[MEMORY_SIZE];
	uint16_t ip;
	uint16_t dp;
	bool running;
} CPU;

void CPU_init(CPU *cpu);

void CPU_loadProgram(CPU *cpu, const uint8_t *program, size_t size);

bool CPU_step(CPU *cpu);

void CPU_run(CPU *cpu);

#endif
