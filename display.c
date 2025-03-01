#include <stdlib.h>
#include <stdio.h>
#include "display.h"

// BytePusher palette (256 colors)
// This is a standard VGA-like palette
static const uint32_t palette[256] = {
    0x000000FF, 0x0000AAFF, 0x00AA00FF, 0x00AAAAFF, 0xAA0000FF, 0xAA00AAFF, 0xAA5500FF, 0xAAAAAAFF,
    0x555555FF, 0x5555FFFF, 0x55FF55FF, 0x55FFFFFF, 0xFF5555FF, 0xFF55FFFF, 0xFFFF55FF, 0xFFFFFFFF,
    
    // Extended palette (remaining colors)
    0x000000FF, 0x00005FFF, 0x000087FF, 0x0000AFFF, 0x0000D7FF, 0x0000FFFF, 0x005F00FF, 0x005F5FFF,
    0x005F87FF, 0x005FAFFF, 0x005FD7FF, 0x005FFFFF, 0x008700FF, 0x00875FFF, 0x008787FF, 0x0087AFFF,
    0x0087D7FF, 0x0087FFFF, 0x00AF00FF, 0x00AF5FFF, 0x00AF87FF, 0x00AFAFFF, 0x00AFD7FF, 0x00AFFFFF,
    0x00D700FF, 0x00D75FFF, 0x00D787FF, 0x00D7AFFF, 0x00D7D7FF, 0x00D7FFFF, 0x00FF00FF, 0x00FF5FFF,
    0x00FF87FF, 0x00FFAFFF, 0x00FFD7FF, 0x00FFFFFF, 0x5F0000FF, 0x5F005FFF, 0x5F0087FF, 0x5F00AFFF,
    0x5F00D7FF, 0x5F00FFFF, 0x5F5F00FF, 0x5F5F5FFF, 0x5F5F87FF, 0x5F5FAFFF, 0x5F5FD7FF, 0x5F5FFFFF,
    0x5F8700FF, 0x5F875FFF, 0x5F8787FF, 0x5F87AFFF, 0x5F87D7FF, 0x5F87FFFF, 0x5FAF00FF, 0x5FAF5FFF,
    0x5FAF87FF, 0x5FAFAFFF, 0x5FAFD7FF, 0x5FAFFFFF, 0x5FD700FF, 0x5FD75FFF, 0x5FD787FF, 0x5FD7AFFF,
    0x5FD7D7FF, 0x5FD7FFFF, 0x5FFF00FF, 0x5FFF5FFF, 0x5FFF87FF, 0x5FFFAFFF, 0x5FFFD7FF, 0x5FFFFFFF,
    0x870000FF, 0x87005FFF, 0x870087FF, 0x8700AFFF, 0x8700D7FF, 0x8700FFFF, 0x875F00FF, 0x875F5FFF,
    0x875F87FF, 0x875FAFFF, 0x875FD7FF, 0x875FFFFF, 0x878700FF, 0x87875FFF, 0x878787FF, 0x8787AFFF,
    0x8787D7FF, 0x8787FFFF, 0x87AF00FF, 0x87AF5FFF, 0x87AF87FF, 0x87AFAFFF, 0x87AFD7FF, 0x87AFFFFF,
    0x87D700FF, 0x87D75FFF, 0x87D787FF, 0x87D7AFFF, 0x87D7D7FF, 0x87D7FFFF, 0x87FF00FF, 0x87FF5FFF,
    0x87FF87FF, 0x87FFAFFF, 0x87FFD7FF, 0x87FFFFFF, 0xAF0000FF, 0xAF005FFF, 0xAF0087FF, 0xAF00AFFF,
    0xAF00D7FF, 0xAF00FFFF, 0xAF5F00FF, 0xAF5F5FFF, 0xAF5F87FF, 0xAF5FAFFF, 0xAF5FD7FF, 0xAF5FFFFF,
    0xAF8700FF, 0xAF875FFF, 0xAF8787FF, 0xAF87AFFF, 0xAF87D7FF, 0xAF87FFFF, 0xAFAF00FF, 0xAFAF5FFF,
    0xAFAF87FF, 0xAFAFAFFF, 0xAFAFD7FF, 0xAFAFFFFF, 0xAFD700FF, 0xAFD75FFF, 0xAFD787FF, 0xAFD7AFFF,
    0xAFD7D7FF, 0xAFD7FFFF, 0xAFFF00FF, 0xAFFF5FFF, 0xAFFF87FF, 0xAFFFAFFF, 0xAFFFD7FF, 0xAFFFFFFF,
    0xD70000FF, 0xD7005FFF, 0xD70087FF, 0xD700AFFF, 0xD700D7FF, 0xD700FFFF, 0xD75F00FF, 0xD75F5FFF,
    0xD75F87FF, 0xD75FAFFF, 0xD75FD7FF, 0xD75FFFFF, 0xD78700FF, 0xD7875FFF, 0xD78787FF, 0xD787AFFF,
    0xD787D7FF, 0xD787FFFF, 0xD7AF00FF, 0xD7AF5FFF, 0xD7AF87FF, 0xD7AFAFFF, 0xD7AFD7FF, 0xD7AFFFFF,
    0xD7D700FF, 0xD7D75FFF, 0xD7D787FF, 0xD7D7AFFF, 0xD7D7D7FF, 0xD7D7FFFF, 0xD7FF00FF, 0xD7FF5FFF,
    0xD7FF87FF, 0xD7FFAFFF, 0xD7FFD7FF, 0xD7FFFFFF, 0xFF0000FF, 0xFF005FFF, 0xFF0087FF, 0xFF00AFFF,
    0xFF00D7FF, 0xFF00FFFF, 0xFF5F00FF, 0xFF5F5FFF, 0xFF5F87FF, 0xFF5FAFFF, 0xFF5FD7FF, 0xFF5FFFFF,
    0xFF8700FF, 0xFF875FFF, 0xFF8787FF, 0xFF87AFFF, 0xFF87D7FF, 0xFF87FFFF, 0xFFAF00FF, 0xFFAF5FFF,
    0xFFAF87FF, 0xFFAFAFFF, 0xFFAFD7FF, 0xFFAFFFFF, 0xFFD700FF, 0xFFD75FFF, 0xFFD787FF, 0xFFD7AFFF,
    0xFFD7D7FF, 0xFFD7FFFF, 0xFFFF00FF, 0xFFFF5FFF, 0xFFFF87FF, 0xFFFFAFFF, 0xFFFFD7FF, 0xFFFFFFFF
};

Display* display_init(SDL_Renderer* renderer, int scale) {
    if (!renderer || scale <= 0) {
        return NULL;
    }

    Display* display = (Display*)malloc(sizeof(Display));
    if (!display) {
        return NULL;
    }

    display->renderer = renderer;
    display->scale = scale;
    
    // Create texture for rendering
    display->texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT
    );

    if (!display->texture) {
        free(display);
        return NULL;
    }

    // Clear pixels
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        display->pixels[i] = 0;
    }

    return display;
}

void display_free(Display* display) {
    if (display) {
        if (display->texture) {
            SDL_DestroyTexture(display->texture);
        }
        free(display);
    }
}

void display_render(Display* display, Memory* memory) {
    // Get display memory address (from bytes 1-3)
    uint32_t pixels_addr = memory_read_address(memory, MEMORY_ADDR_PIXELS);
    
    // Debug info if needed
    static uint32_t last_pixels_addr = 0;
    if (pixels_addr != last_pixels_addr) {
        printf("\nPixel data address changed: 0x%06X\n", pixels_addr);
        last_pixels_addr = pixels_addr;
    }
    
    // Update pixel buffer from memory
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            uint8_t color_index = memory_read_byte(memory, pixels_addr + y * DISPLAY_WIDTH + x);
            display->pixels[y * DISPLAY_WIDTH + x] = palette[color_index];
        }
    }
    
    // Update texture with new pixel data
    SDL_UpdateTexture(display->texture, NULL, display->pixels, DISPLAY_WIDTH * sizeof(uint32_t));
    
    // Clear the renderer
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
    
    // Render the texture scaled to window size
    SDL_Rect dest = {0, 0, DISPLAY_WIDTH * display->scale, DISPLAY_HEIGHT * display->scale};
    SDL_RenderCopy(display->renderer, display->texture, NULL, &dest);
}