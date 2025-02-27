CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lSDL2

SRCS = main.c system.c cpu.c timestamp.c hexdumper.c sdl.c
OBJS = $(SRCS:.c=.o)

bytepusher: $(OBJS)
	$(CC) $(CFLAGS) -o bytepusher $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) bytepusher