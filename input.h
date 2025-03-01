#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include "memory.h"

// BytePusher keyboard state is one byte
typedef struct {
    uint8_t state;
} Input;

// Key mapping
#define KEY_1 (1 << 0)
#define KEY_2 (1 << 1)
#define KEY_3 (1 << 2)
#define KEY_4 (1 << 3)
#define KEY_Q (1 << 4)
#define KEY_W (1 << 5)
#define KEY_E (1 << 6)
#define KEY_R (1 << 7)

// Initialize input
Input* input_init(void);

// Free input resources
void input_free(Input* input);

// Handle SDL event
void input_handle_event(Input* input, SDL_Event* event);

// Update memory with current input state
void input_update_memory(Input* input, Memory* memory);

#endif // INPUT_H