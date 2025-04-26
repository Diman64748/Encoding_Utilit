CC=gcc

CFLAGS=-Wall -Wextra

all:
	$(CC) $(CFLAGS) main.c hex.c to_UTF8.c decoding.c full_analize.c debug_func.c -o program 