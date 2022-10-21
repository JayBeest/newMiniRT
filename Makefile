###               auto-generated Makefile               ###

NAME		=	miniRT

SRC_DIR		=	src/
OBJ_DIR		=	obj/
BIN_DIR		=	bin/
INCL_DIR	=	include/
BIN			=	$(BIN_DIR)$(NAME)

SRC			=	main.c \
				alloc.c
HEADERS		=	datatypes.h \
				alloc.h
OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

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
	$(VECHO) "\033[36mLinking binary file:     \033[0m$@ 🚨"
	$(VECHO)
	$(Q)$(CC) $^ $(CFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INCL_DIR), $(HEADERS))
	$(Q)mkdir -p $(@D)
	$(VECHO) "\033[34mCompiling object file:   \033[0m$@"
	$(Q)$(CC) -c $< $(CFLAGS) -I$(INCL_DIR) -o $@

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
