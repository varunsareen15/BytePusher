#include "hexdumper.h"
#include <stdio.h>
#include <ctype.h>

void hexdump(const uint8_t *data, size_t length) {
	const size_t bytes_per_line = 16;
	for (size_t i = 0; i < length; i += bytes_per_line) {
		printf("%08zx: ", i);
		for (size_t j = 0; j < bytes_per_line; j++) {
			if (i + j < length) {
				printf("%02x ", data[i + j]);
			} else {
				printf("   ");
			}
		}
		printf(" |");
		for (size_t j = 0; j < bytes_per_line; j++) {
			if (i + j < length) {
				uint8_t c = data[i + j];
				printf("%c", isprint(c) ? : '.');
			}
		}
		printf("|\n");
	}
}

#ifdef TEST_HEXDUMPER
// gcc -DTEST_HEXDUMPER hexdumper.c -o hexdumper
int main(void) {
	uint8_t testdata[64];
	for (size_t i = 0; i < sizeof(testData); i++) {
		testData[i] = (uint8_t)i;
	}
	hexdump(testData, sizeof(testData));
	return 0;
}
#endif
