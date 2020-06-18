CC=gcc
CFLAGS=-I.
all : client server

modulo.o: modulo.h
	$(CC) -o modulo.o -c modulo.c $(CFLAGS)
	
client : modulo.o modulo.h
	$(CC) -o client modulo.o client.c -lpthread $(CFLAGS)
	
server: modulo.o modulo.h
	$(CC) -o server modulo.o server.c -lpthread $(CFLAGS)
	
clean:
	rm -f client server modulo.o
