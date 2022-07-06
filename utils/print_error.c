#include "cub.h"

void	error_in_line(char *str, int error)
{
	printf("err - %d\n", error);
	ft_log("in line error");
	ft_putstr_fd(str, 2);
	if (error == EMPTY_IDENTIFER)
		ft_putendl_fd(": no path to texture", 2);
	else if (error == IDENTIFER_ALREADY_EXIST)
		ft_putendl_fd(": identifer alredy present in file", 2);
	else if (error == NOT_RGB)
		ft_putendl_fd(": identifer value not in RGB format", 2);
	else if (error == UNKNOW_SYM)
		ft_putendl_fd(": unexpected symbol", 2);
	else
		ft_putendl_fd(": unknown error", 2);
}

/*void	print_error_2(int error)
{
	if (error == UNKNOW_SYM)
		ft_putendl_fd("cub3d: unknown symbols in config", 2);
	else if (error == UNKNOW_SYM)
		ft_putendl_fd("cub3d: unknown symbols in config", 2);
	else if (error == UNKNOW_SYM)
		ft_putendl_fd("cub3d: unknown symbols in config", 2);
	else if (error == UNKNOW_SYM)
		ft_putendl_fd("cub3d: unknown symbols in config", 2);
	else if (error == UNKNOW_SYM)
		ft_putendl_fd("cub3d: unknown symbols in config", 2);
}*/

void	print_error(int error)
{
	printf("error - %d\n", error);
	if (error == TOO_MANY_ARGS)
		ft_putendl_fd("cub3d: too many arguments passed", 2);
	else if (error == NO_FILE_PASSED)
		ft_putendl_fd("cub3d: no config file passed", 2);
	else if (error == WRONG_FILE_TYPE)
		ft_putendl_fd("cub3d: wrong file type", 2);
	else if (error == EMPTY_FILE)
		ft_putendl_fd("cub3d: empty config file", 2);
	else if (error == INVALID_CONFIG_PARAM)
		ft_putendl_fd("cub3d: invalid config", 2);
	else if (error == NO_MAP_IN_CONFIG)
		ft_putendl_fd("cub3d: map dont found", 2);
	else if (error == INVALID_MAP)
		ft_putendl_fd("cub3d: INVALID_MAP", 2);
	else if (error == TEXTURE_PATH_ERROR)
		ft_putendl_fd("cub3d: file doesn't exist or invalid", 2);
	else if (error == TOO_MANY_PLAYERS)
		ft_putendl_fd("cub3d: two or more players on map", 2);
	else if (error == UNCLOSED_MAP)
		ft_putendl_fd("cub3d: map not closed by walls\
			or empty space inside map", 2);
	else if (error == NO_PLAYER)
		ft_putendl_fd("cub3d: no player on map", 2);
	print_config_format();
}
