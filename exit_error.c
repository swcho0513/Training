#include "header.h"

void exit_error(char *message)
{
	fputs(message, stderr);
	fputs("\n", stderr);
	exit(1);
}
