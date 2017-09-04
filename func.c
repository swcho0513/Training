/******************************************************************************
 *
 *  File Name : func.c
 *
 *  File Create : 2017-09-04
 *  Description : ...
 *
 ******************************************************************************/

#include "header.h"

void block_msg(char *name);
void kick_usr(char *name);

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
		if(command == 'b' || command == 'k')
		{
			tmp = strtok(NULL, " ");
			if(tmp)
			{
				strcpy(targetName, tmp);
				loop = 0;
			}
		}
		else if(command == 'q')
			break;
	}
		

	switch(command)
	{
		case 'b':
			block_msg(targetName);
			break;
		case 'k':
			kick_usr(targetName);
			break;
		case 'q':
			break;
	}
}

void block_msg(char *name)
{
	printf("block [%s]'s msg.\n", name);
}

void kick_usr(char *name)
{
	printf("kick [%s]\n", name);
}
