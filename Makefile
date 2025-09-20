CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -pedantic -Iinclude 

SRC = src/main.c src/basket.c src/hashtable.c src/player.c src/vector.c
OBJS = $(SRC:.c=.o)
PROGRAM = basket

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)

