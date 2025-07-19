NAME = philo

SRC = src/main.c 

INCLUDE = include/philo.h

OBJ = $(SRC:.c=.o) 

CFLAGS = -Wall -Wextra -Werror fsanitize=address

CC = cc

$(NAME): $(OBJ)

all: $(NAME)

%.o:%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rm $(NAME)

re: fclean all

.PHONY: clean
