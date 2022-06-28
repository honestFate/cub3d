
CC			:=	clang
BUILDDIR	:=	object
CFLAGS		:=	-Wall -Wextra -Werror -g
MLXFLAGS	:=	-framework OpenGL -framework AppKit
INC			:=	-I./includes/ -I./gnl/ -I./libft/
INCLUDES	:=	minishell.h color.h
LIB			:=	libft/libft.a

EXECUTE_SRC	=	

PARSER_SRC	=

UTILS_SRC	=	clear.c	color.c  print_default.c  print_error.c  utils.c  validate.c

GNL_SRC		=	get_next_line.c			get_next_line_utils.c

SOURCES := $(PARSER_SRC:%=parser/%) $(EXECUTE_SRC:%=sources/%) $(GNL_SRC:%=gnl/%) main.c
OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.c=.o))


NAME	=	minishell

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking..."
	@make -C ./libft/
	$(CC) $^ -o $(NAME) $(LIB) $(MLXFLAGS)

$(BUILDDIR)/%.o: ./%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -g -c -o $@ $<

clean:
	@make -C ./libft/ clean
	$(RM) -r $(BUILDDIR)

fclean:	clean
	@make -C ./libft/ fclean
	$(RM) -r $(NAME)

re: fclean all

norm:
	@norminette *.c *.h

.PHONY: clean fclean re