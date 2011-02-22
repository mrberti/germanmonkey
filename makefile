NAME = germanmonkey
CFILES = main.c

CC = gcc
CFLAGS = -Wall

all:
	$(CC) $(CFLAGS) -o $(NAME) $(CFILES)

run:
	make && ./$(NAME)
