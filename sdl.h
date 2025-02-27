#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <stdint.h>

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 256
#define SCALE_FACTOR  3  // Scale for better visibilit

void init_sdl();
void update_screen(uint8_t *video_memory);
void handle_events();
void shutdown_sdl();

#endif
