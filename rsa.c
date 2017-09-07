/******************************************************************************
 *
 *  File Name : rsa.c
 *
 *  File Create : 2017-08-25
 *  Description : RSA algorithm
 *
 ******************************************************************************/

#include "header.h"
#include "rsa.h"

void createKey_RSA(int *n, int *e, int *d)
{
  int p, q, pi;

  selectpk(&p, &q);

  *n = p*q;
  pi = (p-1)*(q-1);

  *e = calc_e(pi);
  *d = calc_d(pi, *e);
}

void encrypt_RSA(char *data, int n, int e)
{
  int i, j;
  int sum = 1;
  char enc_msg[128] = "\0";
  char output[128] = "";

  for(i=0; i<strlen(data); i++)
  {
    for(j=0; j<e; j++)
    {
      sum *= (int)data[i];
      sum %= n;
    }
    sprintf(enc_msg, "%d ", sum);
    strcat(output, enc_msg);
    sum = 1;
  }
  strcpy(data, output);
}

void decrypt_RSA(char *data, int n, int d)
{
  int i, j;
  int sum = 1;
  int word;
  char dec_msg[128] = "";
  char *tmp;

  i = 0;

  word = atoi(strtok(data, " "));
  while(word)
  {
    for(j=0; j<d; j++)
    {
      sum *= word;
      sum %= n;
    }
    dec_msg[i++] = (char)sum;
    sum = 1;
    if(tmp = strtok(NULL, " "))
      word = atoi(tmp);
    else
      break;
  }
  strcpy(data, dec_msg);
}

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

int calc_e(int pi)
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
      return i;
    tmp = 1;
  }
}

int calc_d(int pi, int e)
{
  int i;
  for(i=2; i<pi; i++)
  {
    if((e*i) % pi == 1)
      return i;
  }
}
