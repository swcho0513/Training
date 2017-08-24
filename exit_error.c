/******************************************************************************
 *
 *  File Name : exit_error.c
 *
 *  File creation: 2017-08-16
 *  Function : Exit program with print error message
 *
 ******************************************************************************/

#include "header.h"

void exit_error(char *message)
{
	fputs(message, stderr);
	fputs("\n", stderr);
	exit(1);
}
