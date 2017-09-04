/******************************************************************************
 *
 *  File Name : header.h
 *
 *  File Create : 2017-08-16
 *  Description : Header
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define NAMESIZE	130
#define	BUFSIZE		128
#define	ID_LEN		128
#define	PW_LEN		128
#define	MAX_CONNECT	10
#define MAX_USER	100
#define FGETS(str, len, input) { fgets(str, len, input);\
		if(str[strlen(str)-1] = '\n') str[strlen(str)-1] = '\0'; }

void exit_error(char *message);
void user_man();

typedef struct
{
	char id[ID_LEN];
	char pw[PW_LEN];
}User;

User user_DB[MAX_USER];
int user_index;

void encrypt_SHA1(char *data);
void createKey_RSA(int *n, int *e, int *d);
void encrypt_RSA(char *data, int n, int e);
void decrypt_RSA(char *data, int n, int d);

void func();
