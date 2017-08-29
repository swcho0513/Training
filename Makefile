 ###############################################################################
 #
 #  File Name : Makefile
 #
 #  File Create : 2017-08-16
 #
 ###############################################################################

CC = gcc
CFLAGS = 
CTAGS = -pthread
TARGET = server client
HEADER = header.h sha1.h rsa.h
SERV_SRC = server.c exit_error.c $(USER_MAN_SRC) $(SECURE_SRC)
CLNT_SRC = client.c exit_error.c $(USER_MAN_SRC) $(SECURE_SRC)
USER_MAN_SRC = user_man.c
SECURE_SRC = sha1.c sha.c rsa.c

all : $(TARGET)

server : $(SERV_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(SERV_SRC) $(CTAGS)

client : $(CLNT_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(CLNT_SRC) $(CTAGS)

clean :
	rm $(TARGET)

cleandb :
	rm user_db.txt
