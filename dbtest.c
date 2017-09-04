#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv)
{
	sqlite3 *conn;
	sqlite3_stmt *statement;
	int ret = 0;
	int cols, col;

	ret = sqlite3_open("hello.db", &conn);
	if(ret)
	{
		printf("Cannot open DB\n");
		exit(0);
	}

	ret = sqlite3_prepare(conn, "select * from hello", -1, &statement, NULL);
	if(ret != SQLITE_OK)
	{
		printf("Cannot get any DATA\n");
		exit(0);
	}

	cols = sqlite3_column_count(statement);
	
	for(col=0; col<cols; col++)
	{
		printf("%s\n", sqlite3_column_name(statement, col));
	}

	while(1)
	{
		ret = sqlite3_step(statement);
		if(ret == SQLITE_ROW)
		{
			for(col=0; col<cols; col++)
			{
				switch(sqlite3_column_type(statement, col))
				{
					case SQLITE_INTEGER:
						printf("%d\n", sqlite3_column_int(statement, col));
						break;
					case SQLITE_FLOAT:
						printf("%f\n", sqlite3_column_double(statement, col));
						break;
					case SQLITE_TEXT:
						printf("%s\n", sqlite3_column_text(statement, col));
						break;
					case SQLITE_NULL:
						printf("\n");
						break;
				};
			}
		}
		else if(ret == SQLITE_DONE)
		{
			printf("done\n");
			break;
		}
		else
		{
			printf("ret : %d\n", ret);
			break;
		}
	}

	sqlite3_finalize(statement);
	sqlite3_close(conn);

	return 0;
}
