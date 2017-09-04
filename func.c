/******************************************************************************
 *
 *  File Name : func.c
 *
 *  File Create : 2017-09-04
 *  Description : ...
 *
 ******************************************************************************/

#include "header.h"

char func[2+NAMESIZE];

void func()
{
	char command;
	char targetName[NAMESIZE];
	char buf[2+NAMESIZE];
	char tmp[NAMESIZE];

	printf("b username : block [username]'s message\n");
	printf("k username : request kick [username]\n");
	printf("input func : ");

	FGETS(buf, 1+NAMESIZE, stdin);
	tmp = strtok(buf, " ");
	if(tmp)
		command = buf[0];
	tmp = strtok(NULL, " ");
	if(tmp)
		strcpy(targetName, tmp);

	switch(command)
	{
		case 'b':
			block_msg(targetName);
			break;
		case 'k':
			kick_usr(targetName);
			break;
	}
	
	
}

void block_msg(char *name)
{
}

void kick_usr(char *name)
{
}
