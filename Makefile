###               auto-generated Makefile               ###

NAME		=	miniRT

SRC_DIR		=	src/
OBJ_DIR		=	obj/
BIN_DIR		=	bin/
HEADER_DIR	=	include/
BIN			=	$(BIN_DIR)$(NAME)

SRC			=	main.c \
				alloc.c
HEADERS		=	datatypes.h \
				alloc.h
OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

INCL_DIRS	=	include/ MLX42/include/MLX42/
INCLUDES	=	-Ilibft $(addprefix -I, $(INCL_DIRS))

UNAME_P		=	$(shell uname -p)

ifeq ($(UNAME_P), i386)
	LIB		=	-Llibft -lft -L/Users/$(USER)/.brew/opt/glfw/lib/ -lglfw -LMLX42 -lmlx42
else
	LIB		=	-Llibft -lft -L/opt/homebrew/opt/glfw/lib/ -lglfw -LMLX42 -lmlx42
endif

CFLAGS		=	-Wall -Werror -Wextra -pedantic -fsanitize=address -g # -std=c89 -g
CC			=	gcc

ifeq ("$(VERBOSE)","1")
Q :=
VECHO = @echo
else
Q := @
VECHO = @echo
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(Q)mkdir -p $(@D)
	$(VECHO)
	$(VECHO) "\033[35mBuilding libft\033[0m"
	$(Q)make -C libft
	$(VECHO)
	$(VECHO) "\033[35mBuilding MLX42\033[0m"
	$(Q)make -C MLX42
	$(VECHO)
	$(VECHO)
	$(VECHO) "\033[36mLinking binary file:     \033[0m$@ 🚨"
	$(VECHO)
	$(Q)$(CC) $^ $(LIB) $(CFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HEADER_DIR), $(HEADERS))
	$(Q)mkdir -p $(@D)
	$(VECHO) "\033[34mCompiling object file:   \033[0m$@"
	$(Q)$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

clean:
	$(VECHO) "\033[31mRemoving object files\033[0m"
	$(VECHO)
	$(Q)rm -rf $(OBJ_DIR)

fclean: clean
	$(VECHO) "\033[31mRemoving binary\033[0m"
	$(VECHO)
	$(Q)rm -f $(BIN)

re: clean all

.PHONY:	all clean fclean re
