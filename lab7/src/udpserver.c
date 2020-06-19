#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) 
{
	int sockfd, n;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;

	int BUFSIZE = -1;
	int port = -1;
	while (1) 
	{
		int current_optind = optind ? optind : 1;

		static struct option options[] = {{"port", required_argument, 0, 0},
																			{"bufsize", required_argument, 0, 0},
																			{0, 0, 0, 0}};

		int option_index = 0;
		int c = getopt_long(argc, argv, "", options, &option_index);

		if (c == -1)
			break;

		switch (c) 
		{
		case 0: 
		{
			switch (option_index) 
			{
			case 0:
				port = atoi(optarg);
				if (!(port>0))
				return 0;
				break;
			case 1:
				BUFSIZE = atoi(optarg);
				if (!(BUFSIZE>0))
				return 0;
				break;
			default:
				printf("Index %d is out of options\n", option_index);
			}
		} 
			break;
		case '?':
			printf("Unknown argument\n");
			break;
		}
	}
	if (port == -1 || BUFSIZE == -1) 
	{
		fprintf(stderr, "Using: %s --port 20001 --bufsize 4\n", argv[0]);
		return 1;
	}
	char mesg[BUFSIZE], ipadr[16];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("socket problem");
		exit(1);
	}

	memset(&servaddr, 0, SLEN);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	if (bind(sockfd, (SADDR *)&servaddr, SLEN) < 0) 
	{
		perror("bind problem");
		exit(1);
	}
	printf("SERVER starts...\n");

	while (1) 
	{
		unsigned int len = SLEN;

		if ((n = recvfrom(sockfd, mesg, BUFSIZE, 0, (SADDR *)&cliaddr, &len)) < 0) 
		{
			perror("recvfrom");
			exit(1);
		}
		mesg[n] = 0;

		printf("REQUEST %s			FROM %s : %d\n", mesg,
					 inet_ntop(AF_INET, (void *)&cliaddr.sin_addr.s_addr, ipadr, 16),
					 ntohs(cliaddr.sin_port));

		if (sendto(sockfd, mesg, n, 0, (SADDR *)&cliaddr, len) < 0) 
		{
			perror("sendto");
			exit(1);
		}
	}
}
