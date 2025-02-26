#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include "cpu.h"

typedef struct System {
	CPU cpu;
	bool running;
} System;

bool System_init(System *sys);

void System_run(System *sys);

void System_updateDisplay(System *sys);

void System_cleanup(System *sys);

#endif
