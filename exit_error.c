/******************************************************************************
 *
 *  File Name : exit_error.c
 *
 *  File Create : 2017-08-16
 *  Description : Exit program with print error message
 *
 ******************************************************************************/

#include "header.h"

void exit_error(char *message)
{
	fputs(message, stderr);
	fputs("\n", stderr);
	exit(1);
}
