#include "rsa.h"

void selectpk(int *p, int *q)
{
	int random;
	int i, j;
	int ck, ck2 = 0;

	srand((unsigned)time(NULL));
	random = (rand()%100);
	
	for(i=random; 1; i++)
	{
		for(j=2; j<i/2+1; j++)
		{
			if(i%j == 0)
			{
				ck = 1;
				break;
			}
			ck = 0;
		}
		if(ck == 0 && ck2 == 1)
		{
			*q = i;
			break;
		}
		if(ck == 0 && ck2 == 0)
		{
			*p = i;
			ck2 = 1;
		}
	}
}

void selecte(int pi, int *e)
{
	int i, j;
	int tmp = 1;

	for(i=2; i<pi; i++)
	{
		for(j=1; j<=i; j++)
		{
			if(i%j == 0 && pi%j == 0)
				tmp = j;
		}
		if(tmp == 1)
		{
			*e = i;
			break;
		}
		tmp = 1;
	}
}

void selectd(int e, int pi, int *d)
{
	int i;
	for(i=2; i<pi; i++)
	{
		if((e*i) % pi == 1)
			*d = i;
	}
}


int i, j;
int sum = 1;
int word;
char string[128];
char string2[128] = "\0";

int p, q;
int n;
int pi;
int e;
int d;

FILE *output, *input, *output2;

void encrypt_RSA()
{
	output = fopen(ENC_TXT, "w");

	selectpk(&p, &q);

	n = p*q;
	pi = (p-1)*(q-1);

	selecte(pi, &e);
	selectd(e, pi, &d);

	printf("e=%d, d=%d", e, d);

	printf("input : ");
	fgets(string, 1024, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';

	for(i=0; i<strlen(string); i++)
	{
		for(j=0; j<e; j++)
		{
			sum *= (int)string[i];
			sum %= n;
		}
		fprintf(output, "%d\n", sum);
		sum = 1;
	}
	printf("Encrypted in [%s] file\n", ENC_TXT);
	fclose(output);
}
//	__fpurge(stdin);

//	iprintf("Decrypt key input\n");
//	getchar();

void decrypt_RSA(char *input, int n, int d)
{
	char dec_msg[128];
	int i = 0;
	int word;
	
	word = strtok(input, " ");

	while(!word)
	{

		word = (int)strtok(NULL, " ");

		for(j=0; j<d; j++)
		{
			sum *= word;
			sum %= n;
		}
		string2[i] = (char)sum;
		i++;
		sum = 1;
	}

	fputs(string2, output2);
	printf("%s\n", string2);
	printf("Decrypted in [%s] file\n", DEC_TXT);

	fcloseall();

	getchar();
}
