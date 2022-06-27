#ifndef CUB_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
 #include <string.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define CUB_OK 0
# define CUB_ERR 1
# define TOO_MANY_ARGS 2
# define NO_FILE_PASSED 3
# define WRONG_FILE_TYPE 4
# define EMPTY_FILE 5
# define INVALID_CONFIG_PARAM 6
# define NO_MAP_IN_CONFIG 7
# define UNKNOW_SYM 8
# define UNCLOSED_MAP 9
# define EMPTY_IDENTIFER 10
# define IDENTIFER_ALREADY_EXIST 11
# define NOT_RGB 12

# define END_CONFIG 0

# define NORTH_TEXTURE_IDENTIFER "NO"
# define SOUTH_TEXTURE_IDENTIFER "SO"
# define WEST_TEXTURE_IDENTIFER "WE"
# define EAST_TEXTURE_IDENTIFER "EA"
# define FLOOR_COLOR_IDENTIFER "F"
# define CEILLING_COLOR_IDENTIFER "C"

# define MODE_CONFIG 0
# define MODE_MAP 0

#define NO_INDEX 0
#define SO_INDEX 1
#define WE_INDEX 2
#define EA_INDEX 3
#define F_INDEX 4
#define C_INDEX 5

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*north_texture;
	t_img	*south_texture;
	t_img	*west_texture;
	t_img	*east_texture;
	t_img	*current_view;
	int		floor_color;
	int		ceilling_color;
	char	**map;
}	t_cub;

typedef struct s_config
{
	char	**config_txt;
	char	*path_to_texture[4];
	int		colors[2];
}	t_config;


//parser
int		map_parse(t_cub **cub, char *path_to_cfg);

//utils
char	**lst_to_arr(t_list *list, int len);
int		is_space(char c);

void	safe_free(void *data);
void	free_img(t_cub *cub, t_img *img);
void	free_strarr(char **strings);
void	clear_cub(t_cub *cub);

int		check_argv(int argc, char **argv);
int		print_config_format(void);
void	print_error(int error);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif
