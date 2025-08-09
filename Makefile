NAME = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
INCLUDE = include/philo.h
CC = cc

OBJ = $(SRC:.c=.o) 

SRC = src/main.c \
	src/parser.c \
	src/utils.c \
	src/error.c \
	src/init.c \

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

%.o:%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: clean
