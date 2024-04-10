CC := gcc

all: main.c
	$(CC) -pthread main.c -o binary
	./binary

clean: binary
	rm binary