NAME_S = server
NAME_C = client

SOURCES_S = src/server.c src/ft_print_i_d.c
SOURCES_C = src/client.c src/ft_atoi.c src/parsing.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJECTS_S = $(SOURCES_S:.c=.o)
OBJECTS_C = $(SOURCES_C:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJECTS_S) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_S) $(OBJECTS_S)

$(NAME_C): $(OBJECTS_C) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_C) $(OBJECTS_C)

clean:
	rm -f $(OBJECTS_C) $(OBJECTS_S)

fclean: clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re
