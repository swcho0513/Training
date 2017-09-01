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
	fprintf(stderr, "EXIT_ERROR : %s\n", message);
	exit(1);
}
