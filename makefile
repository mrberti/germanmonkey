NAME = germanmonkey
CFILES = main.c

CC = gcc
CFLAGS = -Wall -g

all: $(CFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(CFILES)

run:
	make && ./$(NAME)

clean:
	rm -f $(NAME) a.out
