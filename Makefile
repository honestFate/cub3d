CC			:=	clang
BUILDDIR	:=	object
CFLAGS		:=	-Wall -Wextra -Werror -g
MLX_FOLDER	:=	mlx/
MLXFLAGS	:=	-lXext -lX11 -lbsd -lm
INC			:=	-I./includes/ -I./gnl/ -I./libft/ -I./$(MLX_FOLDER)
INCLUDES	:=	cub.h
LIB			:=	libft/libft.a

PARSER_SRC	=	convert_img.c           parse_config.c          parse_config_line.c     parse_config_map.c      parse_rgb.c             read_config.c

DRAW_SRC	=	minimap.c

UTILS_SRC	=	print_utils.c	clear.c	color.c  print_default.c  print_error.c  utils.c  validate.c

GNL_SRC		=	get_next_line.c			get_next_line_utils.c

SOURCES := $(PARSER_SRC:%=parser/%) $(DRAW_SRC:%=draw/%) $(UTILS_SRC:%=utils/%) $(GNL_SRC:%=gnl/%) main.c
OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.c=.o))


NAME	=	cub3d

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking..."
	@make -C ./$(MLX_FOLDER)
	@make bonus -C ./libft/
	$(CC) $^ -o $(NAME) $(LIB) $(MLXFLAGS) $(MLX_FOLDER)libmlx.a

$(BUILDDIR)/%.o: ./%.c ./includes/$(INCLUDES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -g -c -o $@ $<

clean:
	@make -C ./$(MLX_FOLDER) clean
	@make -C ./libft/ clean
	$(RM) -r $(BUILDDIR)

fclean:	clean
	@make -C ./libft/ fclean
	$(RM) -r $(NAME)

re: fclean all

norm:
	@norminette *.c *.h

.PHONY: clean fclean re
