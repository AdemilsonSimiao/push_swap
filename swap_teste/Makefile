NAME = push_swap
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

SOURCE =	parsing_utils.c \
			validation.c \
			push.c \
			reverse.c \
			rotate.c \
			swap.c \
			sort.c \
			radix.c \
			chunk_utils.c \
			adaptive.c \
			sort_chunk.c \
			options.c \
			disorder.c \
			main_utils.c \
			main.c

LIBFT = ./libft/libft.a

OBJ = $(SOURCE:.c=.o)

all: $(NAME) 

libft:
	make -C ./libft

$(NAME): $(OBJ) libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	make clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

.PHONY: all clean fclean re libft