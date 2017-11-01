#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "sqlite.h"

#define DB_FILE "msglog.db"
#define MSG_LOG "msg.log"

#if 0 // SQL Database
static int callBack(void *NU, int argc, char **argv, char **azColName)
{
  int i;

  for (i = 0; i < argc; i++)
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  printf("\n");

  return 0;
}

/* sendQuery() ; send query to SQLite Database */
// Query strings //
// - READ  : "select *from test";
// - WRITE : "insert into test values(\"%s\", %d);
int sendQuery(const char *query)
{
  sqlite *db = NULL;
  char *ErrMsg = 0;
  int rc = 0;

  db = sqlite_open(DB_FILE, 0, &ErrMsg);
  if ( db == 0 )
  {
    fprintf(stderr, "Can't open database : %s\n", ErrMsg);
    exit(0);
  }

  rc = sqlite_exec(db, query, callback, 0, &ErrMsg);
  if ( rc != SQLITE_OK )
  {
    fprintf(stderr, "SQL error : %s\n", ErrMsg);
    exit(0);
  }

  if (db != NULL) 
  {
    sqlite_close(db);
    db = NULL;
  }

  return 0;
}
#elif 1 // TXT Database
int msgLog(const char *msg)
{
  FILE *fp;
  struct tm *now;
  time_t ltime;
  char ctime[80];

  fp = fopen(MSG_LOG, "a+");

  if ( fp == NULL )
    return -1;

  time(&ltime);
  now = localtime(&ltime);
  sprintf(ctime, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);

  fprintf(fp, "%s %s\n", ctime, msg);
  fclose(fp);

  return 0;
}

int msgSearch(const char *keyword)
{
  FILE *fp;
  char buf[256];
  char *tok;
  char time[20], name[20], msg[80];
  int index = 0;

  fp = fopen(MSG_LOG, "r");

  if ( fp == NULL )
    return -1;

  printf(" *** %s's Message Log *** \n", keyword);

  while(!feof(fp))
  {
    if ( !fgets(buf, 1024, fp) )
      break;
    tok = strtok(buf, " ");
    if (tok)
      strcpy(time, tok);
    tok = strtok(NULL, " ");
    if (tok)
      strcpy(name, tok);
    tok = strtok(NULL, "\n");
    if (tok)
      strcpy(msg, tok);

    if ( !strcmp(keyword, name) )
    {
      index++;
      fprintf(stdout, "%d %s %s %s\n", index, time, name, msg);
    }
  }

  printf(" ***************************\n");

  return 0;
}
#endif
