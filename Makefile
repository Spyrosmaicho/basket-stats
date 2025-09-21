CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -pedantic -Iinclude 

SRC = src/main.c src/io.c src/file_op.c src/player_op.c src/hashtable.c src/player.c src/vector.c src/menu.c src/new_data.c src/file_data.c
OBJS = $(SRC:.c=.o)
PROGRAM = basket

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)

