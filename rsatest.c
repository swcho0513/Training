#include "header.h"

int main()
{
	char input[300] = "";
	int rsa_n, rsa_e, rsa_d;
	while(1)
	{
		createKey_RSA(&rsa_n, &rsa_e, &rsa_d);
		printf("N = %d, E = %d, D = %d\n", rsa_n, rsa_e, rsa_d);
		printf("Input : ");
		FGETS(input, 300, stdin);
		if(!strcmp(input, "q"))
			break;
		encrypt_RSA(input, rsa_n, rsa_e);
		printf("Encrypted : %s\n", input);
		decrypt_RSA(input, rsa_n, rsa_d);
		printf("Decrypted : %s\n", input);
	}

	return 0;
}
