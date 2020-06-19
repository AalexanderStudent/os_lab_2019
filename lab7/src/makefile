CC=gcc
CFLAGS=-I.

all:
	$(CC) -o tcpcl tcpclient.c  
	$(CC) -o tcpserv tcpserver.c 
	$(CC) -o udpcl udpclient.c 
	$(CC) -o udpserv udpserver.c 

clean:
	rm udpserv udpcl tcpserv tcpcl