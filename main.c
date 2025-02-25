#include "bytepusher.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <program_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Initialize emulator and load program
	BytePusher emu;
	init_emulator(&emu);
	load_program(&emu, argv[1]);

	// Initialize SDL graphics
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		window = SDL_CreateWindow("BytePusher Emulator",
					  SDL_WINDOWPOS_CENTERED,
					  SDL_WINDOWPOS_CENTERED,
					  640, 480, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	// Main emulation loop
	while (emu.running) {
		emulate_cycle(&emu);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				emu.running = false;
			}	
		}

		// update display
		if (renderer) {
			render(&emu, renderer);
		}

		// Delay to control emulation speed 
		SDL_Delay(16);
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}
