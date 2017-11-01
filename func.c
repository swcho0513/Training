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
void blockMsg(const char *name);
void kickUser(const char *name);

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
    printf("b name : BLOCK [name]'s MESSAGE\n");
    printf("k name : KICK [name]\n");
    printf("p name : PRINT [name]'s MESSAGE LOG\n");
    printf("q          : QUIT USER_FUCTION\n");
    printf("input func : ");

    FGETS(buf, 2+NAMESIZE, stdin);
    tmp = strtok(buf, " ");
    if (tmp)
      command = buf[0];
    switch(command)
    {
      case 'b':
        tmp = strtok(NULL, " ");
        if (tmp)
        {
          strncpy(targetName, tmp, strlen(tmp));
          //strcpy(targetName, tmp);
          blockMsg(targetName);
          loop = 0;
        }
        break;
      case 'k':
        tmp = strtok(NULL, " ");
        if (tmp)
        {
          strncpy(targetName, tmp, strlen(tmp));
          //strcpy(targetName, tmp);
          kickUser(targetName);
          loop = 0;
        }
        break;
      case 'p':
        tmp = strtok(NULL, " ");
        if (tmp)
        {
          sprintf(targetName, "[%s]", tmp);
          msgSearch(targetName);
          loop = 0;
        }
      case 'q':
        loop = 0;
        break;
    }
  }
  
  return ;
}

void blockMsg(const char *name)
{
  char blockName[NAMESIZE];
  int i;

  if ( check_id(name) == -1 )
    printf("[%s] no exist in chat\n", name);
  else
  {
    sprintf(blockName, "[%s]", name);
    if ( blockCheck(blockName) == -1 )
      printf("%s is already blocked.\n", blockName);
    else
    {
      strncpy(blockUser[block_count], blockName, strlen(blockName));
      //strcpy(blockUser[block_count], blockName);
      block_count++;

      printf("block User : ");
      for (i=0; i<block_count; i++)
        printf("%s ", blockUser[i]);
      printf("\n");
    }
  }

  return ;
}

int blockCheck(const char *name)
{
  int i;

  for (i=0; i<block_count; i++)
  {
    if ( !strcmp(name, blockUser[i]) )
      return -1;
  }
  return 0;
}

void kickUser(const char *name)
{
  if ( check_id(name) == -1 )
    printf("[%s] no exist in chat\n", name);
  else
  {
    printf("kick [%s]\n", name);
  }

  return ;
}
