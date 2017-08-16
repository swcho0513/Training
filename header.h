#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define	BUFSIZE		100
#define	ID_LEN		10
#define	PW_LEN		20
#define	MAX_CONNECT	10

void exit_error(char *message);
// void login(char *name);

#if 0	// login function making...
int login(char *ID, char *PW)
{
	char *input_id
	char *input_pw;
	printf("ID : ");
	fgets(input_id, ID_LEN, stdin);
	// compare ID and DB_id -> if, diff -> loop
	printf("PW : ");
	fgets(input_pw, PW_LEN, stdin);
	// compare PW and DB_id_pw -> if, diff -> return to ID input
#endif

#if 0	// function making


#endif
