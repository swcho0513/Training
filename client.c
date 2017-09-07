/******************************************************************************
 *
 *  File Name : client.c
 *
 *  File Create : 2017-08-16
 *  Description : Chatting client
 *
 ******************************************************************************/

#include "header.h"

void *snd_message(void *arg);
void *rcv_message(void *arg);

char name[NAMESIZE] = "[Default]";
char message[BUFSIZE];
int rsa_n, rsa_e, rsa_d;

int main(int argc, char **argv)
{
  int sock;
  struct sockaddr_in serv_addr;
  pthread_t snd_thread, rcv_thread;
  void *thread_result;

  if(argc != 3)
#if 0
  {
    printf("Usage : %s <ip> <port> \n", argv[0]);
    exit(1);
  }
#endif
#if 1 // for test
  {
    argv[1] = "0.0.0.0";
    argv[2] = "7777";
  }
#endif

  user_man();
  sprintf(name, "[%s]", user_DB[user_index].id);

  if((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    exit_error("socket() error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_addr.sin_port=htons(atoi(argv[2]));

  if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    exit_error("connect() error!");

  printf("Chatting Program Started...\n");

  write(sock, name, strlen(name));

  // Receive RSA Keys.
  char rsa_tmp[20] = "";
  read(sock, rsa_tmp, 16);
  rsa_n = atoi(rsa_tmp);
  read(sock, rsa_tmp, 16);
  rsa_e = atoi(rsa_tmp);
  read(sock, rsa_tmp, 16);
  rsa_d = atoi(rsa_tmp);

  pthread_create(&snd_thread, NULL, snd_message, (void *)(intptr_t) sock);
  pthread_create(&rcv_thread, NULL, rcv_message, (void *)(intptr_t) sock);

  pthread_join(snd_thread, &thread_result);
  pthread_join(rcv_thread, &thread_result);

  close(sock);
  return 0;
}

void *snd_message(void *arg)
{
  int sock = (intptr_t) arg;
  char snd_msg[NAMESIZE+BUFSIZE];
  while(1)
  {
    FGETS(message, BUFSIZE, stdin);
    if(!strcmp(message, "-q"))
    {
      close(sock);
      exit(0);
    }
    else if(!strcmp(message, "-f"))
      func();
    else
    {
      sprintf(snd_msg, "%s %s", name, message);
      encrypt_RSA(snd_msg, rsa_n, rsa_e);
      write(sock, snd_msg, strlen(snd_msg));
    }
  }
}

void *rcv_message(void *arg)
{
  int sock = (intptr_t) arg;
  char rcv_msg[NAMESIZE+BUFSIZE];
  char tok_msg[NAMESIZE+BUFSIZE];
  char *tok_name;
  int str_len;
  while(1)
  {
    str_len = read(sock, rcv_msg, NAMESIZE+BUFSIZE-1);
    if(str_len == -1)
      return (void *)1;
    rcv_msg[str_len] = 0;

    decrypt_RSA(rcv_msg, rsa_n, rsa_d);

    strcpy(tok_msg, rcv_msg);
    tok_name = strtok(tok_msg, " ");
    
    if(blockCheck(tok_name) == 0)
      printf("%s\n", rcv_msg);
  }
}
