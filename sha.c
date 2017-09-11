/******************************************************************************
 *
 *  File Name	: sha.c
 *
 *  File Create	: 2017-08-24
 *  Description	: Encrypt & Decrypt Data with SHA-1
 *
 ******************************************************************************/

#include "header.h"
#include "sha1.h"

void encrypt_SHA1(char *data)
{
  SHA1Context sha;
  uint8_t result[20];

  if(SHA1Reset(&sha))
    exit_error("SHA1 Reset Error");

  if(SHA1Input(&sha, (const unsigned char *)data, strlen(data)))
    exit_error("SHA1 Input Error");

  if(SHA1Result(&sha, result))
    exit_error("SHA1 Result Error : Cannot encrypt data.");

  strcpy(data, result);
}
