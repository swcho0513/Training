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
HEADER = header.h
SERV_SRC = server.c exit_error.c $(USER_MAN_SRC)
CLNT_SRC = client.c exit_error.c $(USER_MAN_SRC)
USER_MAN_SRC = user_man.c sha1.c security.c

all : $(TARGET)

server : $(SERV_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(SERV_SRC) $(CTAGS)

client : $(CLNT_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(CLNT_SRC) $(CTAGS)

clean :
	rm $(TARGET)

cleandb :
	rm user_db.txt
