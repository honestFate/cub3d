#ifndef CUB_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
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
# define INVALID_MAP 9
# define EMPTY_IDENTIFER 10
# define IDENTIFER_ALREADY_EXIST 11
# define NOT_RGB 12
# define END_CONFIG 13
# define TEXTURE_PATH_ERROR 14
# define CANT_CONVERT 15
# define TOO_MANY_PLAYERS 16

# define NORTH_TEXTURE_IDENTIFER "NO"
# define SOUTH_TEXTURE_IDENTIFER "SO"
# define WEST_TEXTURE_IDENTIFER "WE"
# define EAST_TEXTURE_IDENTIFER "EA"
# define FLOOR_COLOR_IDENTIFER "F"
# define CEILLING_COLOR_IDENTIFER "C"

# define PNG 0
# define XPM 1

# define NO_INDEX 0
# define SO_INDEX 1
# define WE_INDEX 2
# define EA_INDEX 3
# define SCREEN_INDEX 4
# define F_INDEX 4
# define C_INDEX 5

# define RIGHT 2
# define LEFT 3
# define DOWN 4
# define UP 5

typedef struct s_point2d
{
	int	x;
	int	y;
}	t_point2d;


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*imgs;
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


/*----------PARSER--------*/

/*----read_config----*/
int	fill_list(int fd, t_list **list);
int	read_config(char ***config, char *path_to_cfg);

/*----parse_config----*/
int		parse_config(t_cub **cub, char *path_to_cfg);
int	parse_settings(t_cub *cub, t_config *config, int *end_of_config);

/*----convert_img----*/
int	convert_img(t_cub *cub, t_config *config);

/*----parse_config_line----*/
int	check_config_param(t_config *cfg);
int	get_identefer_index(char *str);
int	parse_path(t_config *config, char *str, int index);
int	parse_color(t_config *config, char *str, int index);
int	parse_identefer(t_config *config, char *str);

/*----parse_rgb----*/
int	parse_rgb(char *str, int *color);

/*----parse_config_map----*/
int	is_empty_line(char *line);
int	go_rl_direction(char **map, int x, int y, int direction);
int	go_ud_direction(char **map, int x, int y, int direction);
int	draw_board(char **map, int x, int y, int direction);
int	is_closed(char **map, int end_of_config);
int	map_check_valid_sym(t_config *cfg, int start_map);
int	parse_map(t_cub *cub, t_config *cfg, int end_of_config);

/*----------UTILS---------*/

/*----utils----*/
char	**lst_to_arr(t_list *list, int len);
int		is_space(char c);

/*----clear----*/
void	safe_free(void *data);
void	free_img(t_cub *cub, t_img *img);
void	free_strarr(char **strings);
void	clear_cub(t_cub *cub);

/*----validate----*/
int	check_file_type(char *str, char *file_type);
int		check_argv(int argc, char **argv);

/*----print_error----*/
void	print_error(int error);
void	error_in_line(char *str, int error);

/*----print_default----*/
int		print_config_format(void);

/*----color----*/
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif
