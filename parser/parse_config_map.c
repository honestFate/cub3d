#include "cub.h"

int	is_empty_line(char *line)
{
	while (is_space(line++));
	if (!line)
		return (1);
	return (0);
}

int	draw_board(char **map, int x, int y)
{
	draw_board(map, x, y);
}

int	is_closed(char **map, int end_of_config)
{
	//t_point2d	start_pos;
	int	j;

	j = -1;
	while (is_space(map[end_of_config][++j]));
	//start_pos.y = end_of_config;
	//start_pos.x = j;
	map[end_of_config][j] = 's';

}

int	parse_map(t_cub *cub, t_config *cfg, int end_of_config)
{
	int	left_board;
	int	right_board;
	int	j;

	while (cfg->config_txt[end_of_config])
	{
		j = -1;
		if (cfg->config_txt[end_of_config][++j])
		{
			left_board = 
		}
		++end_of_config;
	}
	
}
