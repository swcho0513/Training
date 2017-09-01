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

void selectpk(int *p, int *q);
int calc_e(int pi);
int calc_d(int pi, int e);
