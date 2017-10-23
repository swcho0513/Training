/******************************************************************************
 *
 *  File Name : server.c
 *
 *  File Create : 2017-08-16
 *  Description : Chatting server
 *
 ******************************************************************************/

#include "header.h"

void *clnt_connection(void *arg);
void snd_message(char *message, int len);
void printClnt();

int clnt_number = 0;
int clnt_socks[MAX_CONNECT];
char clnt_name[MAX_CONNECT][NAMESIZE];
char clnt_list[NAMESIZE*10];

pthread_mutex_t mutex;

int main(int argc, char **argv)
{
  int serv_sock;
  int clnt_sock;
  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  int clnt_addr_size;
  pthread_t thread;
  int i;

  if(argc != 2)
#if 0
  {
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }
#endif
#if 1 // for test
  {
    argv[1] = "7777";
  }
#endif

  if(pthread_mutex_init(&mutex, NULL))
    exit_error("pthread_mutex_init() error");

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if(serv_sock == -1)
    exit_error("socket() error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    exit_error("bind() error");

  if(listen(serv_sock, 5) == -1)
    exit_error("listen() error");

  printf("-- Chatting Server Initialized.\n");
  printf("-- Wating for client login.....\n");

  block_count = 0;
  int rsa_n, rsa_e, rsa_d;
  char rsa_tmp[20] = "";
  createKey_RSA(&rsa_n, &rsa_e, &rsa_d);

  while(1)
  {
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    read(clnt_sock, clnt_name[clnt_number], sizeof(clnt_name[clnt_number]));
    printf(" Login  : %s (ip: %s)\n", clnt_name[clnt_number], inet_ntoa(clnt_addr.sin_addr));

    sprintf(rsa_tmp, "%d", rsa_n);
    write(clnt_sock, rsa_tmp, 16);
    sprintf(rsa_tmp, "%d", rsa_e);
    write(clnt_sock, rsa_tmp, 16);
    sprintf(rsa_tmp, "%d", rsa_d);
    write(clnt_sock, rsa_tmp, 16);

    pthread_mutex_lock(&mutex);

    clnt_socks[clnt_number++] = clnt_sock;
    printClnt();

    pthread_mutex_unlock(&mutex);

    write(clnt_sock, clnt_list, NAMESIZE*10);

    pthread_create(&thread, NULL, clnt_connection, (void *)(intptr_t) clnt_sock);
  }
  return 0;
}

void *clnt_connection(void *arg)
{
  int clnt_sock = (intptr_t) arg;
  int msg_len=0;
  char message[BUFSIZE];
  int i;
  char cnt[2];

  while((msg_len = read(clnt_sock, message, sizeof(message))) != 0)
  {
#if 1 // Read & Write Database Function Implementation
    /* write message log to sql db */
    if( sendQuery("create table msgLog(name char(20), msg char(80))") == 0 )
      exit_error("sendQuery() error");
    if( sendQuery("insert into msgLog values(name, msg)") == 0 )
      exit_error("sendQuery() error");
#elif 0
    if( sendQuery("select * from msgLog") == 0 )
      exit_error("sendQuery() error");
#endif

#if 1 // print user list function
    if(!strcmp(message, "l"))
    {
      snd_message(clnt_list, NAMESIZE*10);
    }
#elif 0
    {
      sprintf(cnt, "%d", clnt_number);
      snd_message(cnt, 1);
      for(i=0; i<clnt_number; i++)
      {
        printf("send to %s\n", clnt_name[i]);
        snd_message(clnt_name[i], NAMESIZE);
      }
    }
#endif
    else
      snd_message(message, msg_len);
  }

  pthread_mutex_lock(&mutex);
  for(i=0; i<clnt_number; i++)
  {
    if(clnt_sock == clnt_socks[i])
    {
      printf(" Logout : %s\n", clnt_name[i]);
      for(; i<clnt_number-1; i++)
      {
        clnt_socks[i] = clnt_socks[i+1];
        strcpy(clnt_name[i], clnt_name[i+1]);
      }
      break;
    }
  }
  clnt_number--;
  printClnt();
  pthread_mutex_unlock(&mutex);
  close(clnt_sock);

  return 0;
}

void snd_message(char *message, int len)
{
  int i;
  pthread_mutex_lock(&mutex);
  for(i=0; i<clnt_number; i++)
    write(clnt_socks[i], message, len);
  //cmjeong edit
  memset(message,0,sizeof(message));
  pthread_mutex_unlock(&mutex);
}

void printClnt()
{
  int i;

  printf(" ----- Clnt List ----- \n");
  strcpy(clnt_list, " User List : ");
  for(i=0; i<clnt_number; i++)
  {
    printf("%s", clnt_name[i]);
    strcat(clnt_list, clnt_name[i]);
  }
  printf("\n --------------------- \n");
}
