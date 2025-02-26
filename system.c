#include "system.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

bool System_init(System *sys) {
	CPU_init(&sys->cpu);

	sys->running = true;

	printf("System initialized.\n");
	return true;
}

void System_updateDisplay(System *sys) {
	printf("Display update - first 16 bytes: ");
	for (int i = 0; i < 16; i++) {
		printf("%02x ", sys->cpu.memory[i]);
	}
	printf("\n");
}

void System_run(System *sys) {
	while (sys->running && sys->cpu.running) {
		if (!CPU_step(&sys->cpu)) {
			break;
		}
		System_updateDisplay(sys);
	}
}

void System_cleanup(System *sys) {
	printf("System cleanup complete.\n");
}
