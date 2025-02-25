#ifndef BYTEPUSHER_H
#define BYTEPUSHER_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 65536

typedef struct {
	uint8_t memory[MEMORY_SIZE];
	uint8_t pc; //Program Counter
	uint8_t pointer; 
	bool running; //control emulation loop
} BytePusher;



//Initialize emulator state
void init_emulator(BytePusher *emu);

//Load a program into memory from file
void load_program(BytePusher *emu, const char *filename);

// Execute one emulation cycle (fetch, decode, execute)
void emulate_cycle(BytePusher *emu);

// Decode and execute opcode
void execute_instruction(BytePusher *emu, uint8_t opcode);

//Render graphical output using SDL2
void render(BytePusher *emu, SDL_Renderer *rederer);

#endif // BYTEPUSHER_H


