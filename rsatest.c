#include "header.h"

int main()
{	
	char input[300] = "";
	int n, e, d;
	createKey_RSA(&n, &e, &d);
	while(1)
	{
		printf(" : ");
		FGETS(input, 300, stdin)
		if(!strcmp(input, "q"))
			break;
		printf("input msg : %s\n", input);
		encrypt_RSA(input, n, e);
		printf("encrypted : %s\n", input);
		decrypt_RSA(input, n, d);
		printf("decrypted : %s\n", input);
	}
	return 0;
}
