
CC			:=	clang
BUILDDIR	:=	object
CFLAGS		:=	-Wall -Wextra -Werror -g
MLXFLAGS	:=	-framework OpenGL -framework AppKit
INC			:=	-I./includes/ -I./gnl/ -I./libft/ -I./minilibx_macos/
INCLUDES	:=	minishell.h color.h
LIB			:=	libft/libft.a

PARSER_SRC	=	convert_img.c           parse_config.c          parse_config_line.c     parse_config_map.c      parse_rgb.c             read_config.c

UTILS_SRC	=	clear.c	color.c  print_default.c  print_error.c  utils.c  validate.c

GNL_SRC		=	get_next_line.c			get_next_line_utils.c

SOURCES := $(PARSER_SRC:%=parser/%) $(UTILS_SRC:%=utils/%) $(GNL_SRC:%=gnl/%) main.c
OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.c=.o))


NAME	=	minishell

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking..."
	@make bonus -C ./libft/
	$(CC) $^ -o $(NAME) $(LIB) $(MLXFLAGS) ./minilibx_macos/libmlx.a

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
