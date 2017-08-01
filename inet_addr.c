#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned int conv_addr;
	conv_addr = inet_addr(argv[1]);

	if(conv_addr == INADDR_NONE)
		printf("Error Occur : %d \n", conv_addr);
	else
		printf("Unsigned long addr(network ordered) : %x \n", conv_addr);
	return 0;
}
