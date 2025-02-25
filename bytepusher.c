#include "bytepusher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_emulator(BytePusher *emu) {
	memset(emu->memory, 0, MEMORY_SIZE);
	emu->pc = 0;
	emu->pointer = 0;
	emu->running = true;
}

void load_program(BytePusher *emu, const char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		perror("Failed to open program file");
		exit(EXIT_FAILURE);
	}
	fread(emu->memory, sizeof(uint8_t), MEMORY_SIZE, fp);
	fclose(fp);
}

void execute_instruction(BytePusher *emu, uint8_t opcode) {
	switch (opcode) {
		case 0x00:
			//halt instruction
			emu->running = false;
			break;
		default:
			fprintf(stderr, "Unknown opcode: 0x%02X at address 0x%08X\n", opcode, emu->pc);
			emu->running = false;
			break;
	}
}

void emulate_cycle(BytePusher *emu) {
	uint8_t opcode = emu->memory[emu->pc];
	emu->pc++;
	execute_instruction(emu, opcode);
}

void render(BytePusher *emu, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

