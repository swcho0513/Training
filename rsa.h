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

void    selectPK(int *p, int *q);
int     calcE(const int pi);
int     calcD(const int pi, const int e);
