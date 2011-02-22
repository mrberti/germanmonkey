NAME = germanmonkey
CFILES = main.c

CC = gcc
CFLAGS = -Wall -g

all: $(CFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(CFILES)

clean:
	rm -f *.o $(NAME)
