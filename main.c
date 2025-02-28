#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "timestamp.h"
#include "hexdumper.h"
#include "cpu.h"
#include "sdl.h"

void load_program_from_file(System *sys, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    if (file_size > MEMORY_SIZE) {
        printf("Warning: Program is too large! Truncating to %d bytes.\n", MEMORY_SIZE);
        file_size = MEMORY_SIZE;
    }

    fread(sys->cpu.memory, 1, file_size, file);
    fclose(file);

    // ✅ Print first 32 bytes of loaded program
    printf("Loaded program (%zu bytes):\n", file_size);
    for (size_t i = 0; i < 32 && i < file_size; i++) {
        printf("%02X ", sys->cpu.memory[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
        printf("Usage: %s <BytePusher program>\n", argv[0]);
        return EXIT_FAILURE;
    }

    System sys;
    if (!System_init(&sys)) {
        fprintf(stderr, "System initialization failed.\n");
        return EXIT_FAILURE;
    }

    // ✅ Load the program from file
    load_program_from_file(&sys, argv[1]);

    // ✅ Start SDL
    init_sdl();

    // ✅ Run CPU and update display
    while (sys.running) {
        handle_events();
        System_run(&sys);
        update_screen(sys.cpu.memory);
        SDL_Delay(16);
    }

    shutdown_sdl();
    System_cleanup(&sys);
    return EXIT_SUCCESS;
}
