#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include "memory.h"

// BytePusher display is 256x256 pixels
#define DISPLAY_WIDTH 256
#define DISPLAY_HEIGHT 256

typedef struct {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT];
    int scale;
} Display;

// Initialize display
Display* display_init(SDL_Renderer* renderer, int scale);

// Free display resources
void display_free(Display* display);

// Render display from memory
void display_render(Display* display, Memory* memory);

#endif // DISPLAY_H