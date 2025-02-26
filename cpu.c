#include "cpu.h"
#include <stdio.h>

void CPU_init(CPU *cpu) {
	cpu->ip = 0;
	cpu->dp = 0;
	cpu->running = true;
	for (size_t i = 0; i < MEMORY_SIZE; i++) {
		cpu->memory[i] = 0;
	}
}

void CPU_loadProgram(CPU *cpu, const uint8_t *program, size_t size) {
	if (size > MEMORY_SIZE) {
		size = MEMORY_SIZE;
	}
	for (size_t i = 0; i < size; i++) {
		cpu->memory[i] = program[i];
	}
}

bool CPU_step(CPU *cpu) {
	if (cpu ->ip >= MEMORY_SIZE) {
		cpu->running = false;
		return false;
	}

	uint8_t opcode = cpu->memory[cpu->ip];

	switch (opcode) {
		case 0x00:
			cpu->running = false;
			break;
		case 0x01:
			cpu->dp = (cpu->dp + 1) % MEMORY_SIZE;
			break;
		case 0x02:
			cpu->dp = (cpu->dp - 1) % MEMORY_SIZE;
			break;
		case 0x03:
			cpu->memory[cpu->dp]++;
			break;
		case 0x04:
			cpu->memory[cpu->dp]--;
			break;
		case 0x05:
			putchar(cpu->memory[cpu->dp]);
			break;
		case 0x06: {
			int c = getchar();
			if (c != EOF) {
				cpu->memory[cpu->dp] = (uint8_t)c;
			}
			break;
		}
		case 0x07:
			if (cpu->memory[cpu->dp] == 0) {
				uint16_t nested = 1;
				while (nested && ++cpu->ip < MEMORY_SIZE) {
					if (cpu->memory[cpu->ip] == 0x07) {
						nested++;
					} else if (cpu->memory[cpu->ip] == 0x08) {
						nested--;	
					}
				}
			}
			break;
		default:
			fprintf(stderr, "Unkown opcode 0x%02X at address %u\n", opcode, cpu->ip);
			cpu->running = false;
			break;
	}
	cpu->ip++;
	return cpu->running;
}


void CPU_run(CPU *cpu) {
	while (cpu->running) {
		CPU_step(cpu);
	}
}
