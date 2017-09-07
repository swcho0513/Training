/******************************************************************************
 *
 *  File Name : func.c
 *
 *  File Create : 2017-09-04
 *  Description : ...
 *
 ******************************************************************************/

#include "header.h"

void printUser();
void blockMsg(char *name);
void kickUser(char *name);

void func()
{
  char command;
  char targetName[NAMESIZE];
  char buf[2+NAMESIZE];
  char *tmp;
  int loop = 1;

  while(loop)
  {
    printf("----------  USER_FUNCTION  ----------\n");
    printf("b username : BLOCK [username]'s MESSAGE\n");
    printf("k username : KICK [username]\n");
    printf("q          : QUIT USER_FUCTION\n");
    printf("input func : ");

    FGETS(buf, 2+NAMESIZE, stdin);
    tmp = strtok(buf, " ");
    if(tmp)
      command = buf[0];
    switch(command)
    {
      case 'b':
        tmp = strtok(NULL, " ");
        if(tmp)
        {
          strcpy(targetName, tmp);
          blockMsg(targetName);
          loop = 0;
        }
        break;
      case 'k':
        tmp = strtok(NULL, " ");
        if(tmp)
        {
          strcpy(targetName, tmp);
          kickUser(targetName);
          loop = 0;
        }
        break;
      case 'q':
        loop = 0;
        break;
    }
  }
}

void blockMsg(char *name)
{
  char blockName[NAMESIZE];
  int i;

  if(check_id(name) == -1)
    printf("[%s] no exist in chat\n", name);
  else
  {
    sprintf(blockName, "[%s]", name);
    if(blockCheck(blockName) == -1)
      printf("%s is already blocked.\n", blockName);
    else
    {
      strcpy(blockUser[block_count], blockName);
      block_count++;

      printf("block User : ");
      for(i=0; i<block_count; i++)
        printf("%s ", blockUser[i]);
      printf("\n");
    }
  }
}

int blockCheck(char *name)
{
  int i;

  for(i=0; i<block_count; i++)
  {
    if(!strcmp(name, blockUser[i]))
      return -1;
  }
  return 0;
}

void kickUser(char *name)
{
  printf("kick [%s]\n", name);
}

