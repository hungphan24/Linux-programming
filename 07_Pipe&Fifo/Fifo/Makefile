CC := gcc

all: Server/main.c
	$(CC) Client/main.c -o client
	$(CC) Server/main.c -o server

clean:
	rm -f client server
