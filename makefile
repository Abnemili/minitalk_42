NAME_S = server
NAME_C = client

SOURCES_S = server.c functions.c
SOURCES_C = client.c functions.c ft_atoi.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJECTS_S = $(SOURCES_S:.c=.o)
OBJECTS_C = $(SOURCES_C:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJECTS_S)
	$(CC) $(CFLAGS) -o $(NAME_S) $(OBJECTS_S)

$(NAME_C): $(OBJECTS_C)
	$(CC) $(CFLAGS) -o $(NAME_C) $(OBJECTS_C)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS_S) $(OBJECTS_C)

fclean: clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re