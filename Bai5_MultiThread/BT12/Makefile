CC := gcc

all: main.c
	$(CC) -pthread main.c -o binary
	./binary

clean: binary students.txt
	rm binary
	rm students.txt