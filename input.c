#include <stdlib.h>
#include "input.h"

Input* input_init(void) {
    Input* input = (Input*)malloc(sizeof(Input));
    if (!input) {
        return NULL;
    }

    input->state = 0;
    return input;
}

void input_free(Input* input) {
    if (input) {
        free(input);
    }
}

void input_handle_event(Input* input, SDL_Event* event) {
    if (!input || !event) {
        return;
    }

    // Key mapping
    uint8_t key_mask = 0;
    
    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
        bool pressed = (event->type == SDL_KEYDOWN);
        
        switch (event->key.keysym.sym) {
            case SDLK_1: key_mask = KEY_1; break;
            case SDLK_2: key_mask = KEY_2; break;
            case SDLK_3: key_mask = KEY_3; break;
            case SDLK_4: key_mask = KEY_4; break;
            case SDLK_q: key_mask = KEY_Q; break;
            case SDLK_w: key_mask = KEY_W; break;
            case SDLK_e: key_mask = KEY_E; break;
            case SDLK_r: key_mask = KEY_R; break;
            default: return;  // Ignore other keys
        }
        
        // Update key state
        if (pressed) {
            input->state |= key_mask;  // Set bit
        } else {
            input->state &= ~key_mask;  // Clear bit
        }
    }
}

void input_update_memory(Input* input, Memory* memory) {
    if (!input || !memory) {
        return;
    }

    // Write keyboard state to memory
    memory_write_byte(memory, MEMORY_ADDR_KEYBOARD, input->state);
}