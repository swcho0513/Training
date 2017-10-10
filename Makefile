 ###############################################################################
 #
 #  File Name : Makefile
 #
 #  File Create : 2017-08-16
 #
 ###############################################################################

CC = gcc
CFLAGS = 
CTAGS = -pthread -lsqlite
TARGET = server client
HEADER = header.h sha1.h rsa.h
SERV_SRC = server.c exit_error.c $(USER_MAN_SRC) $(SECURE_SRC) $(FUNC_SRC) database.c
CLNT_SRC = client.c exit_error.c $(USER_MAN_SRC) $(SECURE_SRC) $(FUNC_SRC)
USER_MAN_SRC = user_man.c 
SECURE_SRC = sha1.c sha.c rsa.c
FUNC_SRC = func.c

all : $(TARGET)

server : $(SERV_SRC) $(HEADER)
	@$(CC) $(CFLAGS) -o $@ $(SERV_SRC) $(CTAGS)
	@echo "MAKE [server]"

client : $(CLNT_SRC) $(HEADER)
	@$(CC) $(CFLAGS) -o $@ $(CLNT_SRC) $(CTAGS)
	@echo "MAKE [client]"

clean :
	@rm $(TARGET)
	@echo "REMOVE EXEC FILES"

cleandb :
	@rm User_db.txt
	@echo "REMOVE DB FILE"
