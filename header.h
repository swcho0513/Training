/******************************************************************************
 *
 *  File Name : header.h
 *
 *  File Create : 2017-08-16
 *  Description : Header
 *
 ******************************************************************************/

#ifndef __TRAINING_H__
#define __TRAINING_H__

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <syslog.h>
#include <netinet/in.h>
#include <pthread.h>

#define NAMESIZE	        130
#define	BUFSIZE		        2048
#define	ID_LEN		        128
#define	PW_LEN		        128
#define	MAX_CONNECT	        10
#define MAX_USER	        100
#define FGETS(str, len, input)  { fgets(str, len, input);\
                if ( str[strlen(str)-1] = '\n' ) str[strlen(str)-1] = '\0'; }

typedef struct
{
  char  id[ID_LEN];
  char  pw[PW_LEN];
} User;

struct Keyword
{
  char  name[20];
  char  msg[80];
  char  time[20];
};

User    user_DB[MAX_USER];
int     user_index;
char    blockUser[MAX_CONNECT][ID_LEN];
int     block_count;

void    exit_error(const char *message);
void    user_man();
int     check_id(const char *input);
int     blockCheck(const char *name);
void    func();
int     sendQuery(const char *query);
int     msgLog(const char *msg);
int     msgSearch(const char *keyword);
void    encrypt_SHA1(char *data);
void    createKey_RSA(int *n, int *e, int *d);
void    encrypt_RSA(char *data, const int n, const int e);
void    decrypt_RSA(char *data, const int n, const int d);

#endif
