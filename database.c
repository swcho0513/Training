#include <stdio.h>
#include <stdlib.h>
#include "sqlite.h"

#define DB_FILE "msglog.db"

static int callback(void *NU, int argc, char **argv, char **azColName)
{
  int i;

  for( i = 0; i < argc; i++ )
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  printf("\n");
  return 0;
}

/* sendQuery() ; send query to SQLite Database */
// Query strings //
// - READ  : "select *from test";
// - WRITE : "insert into test values(\"%s\", %d);
int sendQuery(char *query)
{
  sqlite *db;
  char *ErrMsg = 0;
  int rc;

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

  sqlite_close(db);
  return 0;
}
