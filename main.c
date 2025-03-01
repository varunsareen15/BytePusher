#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "memory.h"
#include "cpu.h"
#include "display.h"
#include "input.h"

#define TITLE "BytePusher Emulator"
#define SCALE 4
#define FPS 60
#define FRAME_TIME_MS (1000 / FPS)

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <bytepusher_rom>\n", argv[0]);
        return 1;
    }

    // Initialize memory
    Memory* memory = memory_init();
    if (!memory) {
        fprintf(stderr, "Failed to initialize memory\n");
        return 1;
    }

    // Load ROM
    if (!memory_load_rom(memory, argv[1])) {
        fprintf(stderr, "Failed to load ROM: %s\n", argv[1]);
        memory_free(memory);
        return 1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        memory_free(memory);
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DISPLAY_WIDTH * SCALE, DISPLAY_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        memory_free(memory);
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        memory_free(memory);
        return 1;
    }

    // Initialize display
    Display* display = display_init(renderer, SCALE);
    if (!display) {
        fprintf(stderr, "Failed to initialize display\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        memory_free(memory);
        return 1;
    }

    // Initialize input
    Input* input = input_init();
    if (!input) {
        fprintf(stderr, "Failed to initialize input\n");
        display_free(display);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        memory_free(memory);
        return 1;
    }

    // Initialize CPU
    CPU* cpu = cpu_init(memory, display, input);
    if (!cpu) {
        fprintf(stderr, "Failed to initialize CPU\n");
        input_free(input);
        display_free(display);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        memory_free(memory);
        return 1;
    }

    // Main emulation loop
    bool running = true;
    SDL_Event event;
    Uint32 frame_start, frame_time;
    
    // Initialize with PC pointing to byte 0
    memory_write_byte(memory, MEMORY_ADDR_PC, 0x01);
    memory_write_byte(memory, MEMORY_ADDR_PC + 1, 0x00);
    memory_write_byte(memory, MEMORY_ADDR_PC + 2, 0x00);

    printf("Emulator started. Press ESC to exit.\n");

    while (running) {
        frame_start = SDL_GetTicks();

        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            } else {
                input_handle_event(input, &event);
            }
        }

        // Update input state in memory
        input_update_memory(input, memory);

        // Execute CPU instructions for one frame
        cpu_execute_frame(cpu);

        // Render display
        display_render(display, memory);
        SDL_RenderPresent(renderer);

        // Debug output - show current PC and frame time
        uint32_t pc = memory_read_address(memory, MEMORY_ADDR_PC);
        frame_time = SDL_GetTicks() - frame_start;
        printf("\rPC: 0x%06X | Frame time: %dms | FPS: %.1f   ", 
               pc, frame_time, (frame_time > 0) ? 1000.0f / frame_time : 0);
        fflush(stdout);

        // Cap to 60 FPS
        if (frame_time < FRAME_TIME_MS) {
            SDL_Delay(FRAME_TIME_MS - frame_time);
        }
    }

    printf("\nEmulator stopped.\n");

    // Cleanup
    cpu_free(cpu);
    input_free(input);
    display_free(display);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    memory_free(memory);

    return 0;
}