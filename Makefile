ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I inc/ \
		-I ./libft/includes/

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = gcc -Wall -Werror -Wextra -fPIC

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	$(GCC) -o $(NAME) $(OBJ) -shared
	rm -rf libft_malloc.so
	ln -s $(NAME) libft_malloc.so

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(GCC) $(INC) -c $< -o $@

./libft/libft.a:
	make -C libft

clean:
	make clean -C libft
	rm -rf libft_malloc.so
	rm -rf $(OBJ)

fclean: clean
	rm -rf libft/libft.a
	rm -rf libft_malloc.so
	rm -rf $(NAME)

re: fclean all