NAME		=	miniRT

SRC_DIR		=	src/
OBJ_DIR		=	obj/
BIN_DIR		=	bin/
HEADER_DIR	=	include/
BIN			=	$(BIN_DIR)$(NAME)

SRC			=	main.c \
				rt_init.c \
				rt_check_infile.c \
				rt_alloc.c \
				rt_parser.c \
				rt_math_utils.c \
				rt_scene_printer.c \
				rt_vector_utils.c \
				rt_draw_utils.c \
				rt_rotate.c \
				rt_color.c \
				rt_render.c \
				rt_render_utils.c \
				rt_msaa.c \
				rt_trace.c \
				rt_intersect.c \
				rt_light.c \
				rt_hook.c \
				rt_controls.c \
				rt_time.c \
				rt_thread.c \
				rt_error.c \


HEADERS		=	rt_datatypes.h \
				rt_init.h \
				rt_check_infile.h \
				rt_alloc.h \
				rt_parser.h \
				rt_math_utils.h \
				rt_scene_printer.h \
				rt_vector_utils.h \
				rt_render_utils.h \
				rt_rotate.h \
				rt_draw_utils.h \
				rt_color.h \
				rt_render.h \
				rt_render_utils.h \
				rt_msaa.h \
				rt_trace.h \
				rt_intersect.h \
				rt_light.h \
				rt_hook.h \
				rt_controls.h \
				rt_time.h \
				rt_thread.h \
				rt_error.h \


OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

INCL_DIRS	=	include/ MLX42/include/MLX42/
INCLUDES	=	-Ilibft $(addprefix -I, $(INCL_DIRS))

UNAME		=	$(shell uname)
UNAME_P		=	$(shell uname -p)


ifeq ($(UNAME_P), i386)
	LIB		=	-Llibft -lft -L/Users/$(USER)/.brew/opt/glfw/lib/ -lglfw -LMLX42 -lmlx42
else
	LIB		=	-Llibft -lft -L/opt/homebrew/opt/glfw/lib/ -lglfw -LMLX42 -lmlx42
endif

ifeq ($(UNAME), Linux)
	LIB		=	-Llibft -LMLX42 -lft -lmlx42 -ldl -lglfw3 -pthread -lm
endif

CFLAGS		=	-Wall -Werror -Wextra -pedantic -O1 #-fsanitize=address -g # -std=c89 -g
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
	$(Q)$(CC) $^ $(CFLAGS) -o $@ $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HEADER_DIR), $(HEADERS))
	$(Q)mkdir -p $(@D)
	$(VECHO) "\033[34mCompiling object file:   \033[0m$@"
	$(Q)$(CC) -c $< $(CFLAGS) -o $@ $(INCLUDES)

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
