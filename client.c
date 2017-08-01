#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9000

int main(void)
{
	int sd, len;
	char buf[256], msg[256];
	struct sockaddr_in sin;

	memset((char*)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("119.194.249.38");

	while (1)
	{
		if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}
		printf("==>create socket\n");

		if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
			perror("connect");
			exit(1);
		}
		printf("==>connect server\n");

		if (recv(sd, buf, sizeof(buf) + 1, 0) == -1) {
			perror("recv");
			exit(1);
		}
		//    buf[strlen]='\0';
		printf("==>from server : %s\n", buf);
		//printf("sizeof: %d\n", sizeof(buf));
		//printf("strlen: %d\n", strlen(buf));
		gets(msg);
		if (send(sd, msg, strlen(msg) + 1, 0) == -1) {
			perror("send");
			exit(1);
		}
	}
	close(sd);

	return 0;
}
