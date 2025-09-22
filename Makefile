CFLAGS = -g3 -Wall -Wextra -Werror -pedantic -Iinclude -MMD -MP

SRC = src/main.c src/io.c src/file_op.c src/player_op.c src/hashtable.c \
      src/player.c src/vector.c src/menu.c src/new_data.c src/file_data.c \
      src/team.c src/error.c src/add_stats.c src/validate_stats.c

OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)
PROGRAM = basket

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

-include $(DEPS)

clean:
	rm -f $(PROGRAM) $(OBJS) $(DEPS)
