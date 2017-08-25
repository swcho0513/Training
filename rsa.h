/******************************************************************************
 *
 *  File Name : rsa.h
 *
 *  File Create : 2017-08-25
 *  Description : Header File for rsa algoritm code
 *
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int p, q, pi;
int n, e, d;

void selectPK(int *p, int *q);
void selectE(int pi, int *e);
void selectD(int pi, int e, int *d);

// void createKey(int p, int q);
