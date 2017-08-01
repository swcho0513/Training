#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<netinet/in.h>

#define PORTNUM 9000

int main(void) {
	int i;
	char buf[256];
	char buf2[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	printf("** Create Socket\n");

	memset((char*)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("119.194.249.14");

	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}
	printf("** Bind Socket \n");

	if (listen(sd, 15)) {
		perror("listen");
		exit(1);
	}
	printf("*** Listen Socket\n");

	i = 0;

	while (1) {
		if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
			perror("accept");
			exit(1);
		}

		else if (ns != -1 && i == 0)
			printf(" Acept Client\n");

		switch (fork()) {
		case 0:
			if (i == 0) {
				printf("** Fork Client\n");
				i++;
			}
			close(sd);

			printf("Enter msg:");
			gets(buf);

			if (send(ns, buf, strlen(buf) + 1, 0) == -1) {
				perror("send");
				exit(1);
			}

			if (recv(ns, buf, sizeof(buf), 0) == -1) {
				perror("recv");
				exit(1);
			}

			printf("\n**From Client: %s\n", buf);
			exit(0);
		}
		close(ns);
	}
	return 0;
}
