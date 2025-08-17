NAME = philo

CFLAGS = -Wall -Wextra -Werror #-pthread #-fsanitize=address -g
INCLUDE = include/philo.h include/colors.h include/struct.h
CC = cc

OBJ = $(SRC:.c=.o) 

SRC = src/main.c \
	src/parser.c \
	src/utils.c \
	src/error.c \
	src/init.c \
	src/simulation.c \
	src/get_and_set.c \
	src/utils_simulation.c \
	src/message.c \
	src/monitor.c \
	src/cleanup.c \

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
