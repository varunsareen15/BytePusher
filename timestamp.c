#include "timestamp.h"
#include <sys/time.h>
#include <stddef.h>

uint64_t get_timestamp_microseconds(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((uint64_t)tv.tv_sec * 1000000ULL) + tv.tv_usec;
}

uint64_t get_timestamp_milliseconds(void) {
	return get_timestamp_microseconds() / 1000ULL;
}
