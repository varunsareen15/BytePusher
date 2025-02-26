#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "timestamp.h"
#include "hexdumper.h"
#include "cpu.h"

int main(void) {
	System sys;

	if (!System_init(&sys)) {
		fprintf(stderr, "System initialization failed.\n");
		return EXIT_FAILURE;
	}
	uint8_t program[] = { 0x03, 0x05, 0x00 };
	CPU_loadProgram(&sys.cpu, program, sizeof(program));

	printf("Memory dump before execution:\n");
	hexdump(sys.cpu.memory, 64);

	uint64_t start_time = get_timestamp_milliseconds();

	System_run(&sys);

	uint64_t end_time = get_timestamp_milliseconds();
	printf("Execution took %llu milliseconds\n", (unsigned long long)(end_time - start_time));

	printf("Memory dump after execution:\n");
	hexdump(sys.cpu.memory, 64);

	System_cleanup(&sys);
	
	return EXIT_SUCCESS;
}
