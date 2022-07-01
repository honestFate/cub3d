#include "cub.h"

int	is_empty_line(char *line)
{
	while (is_space(line++));
	if (!line)
		return (1);
	return (0);
}

int	go_rl_direction(char **map, int x, int y, int direction)
{
	map[y][x] = '2';
	if (direction == RIGHT)
	{
		if ((y > 0 && map[y - 1][x] == '1'
			&& !draw_board(map, x, y - 1, UP))
			|| (map[y][x + 1] == '1'
			&& !draw_board(map, x + 1, y, RIGHT))
			|| (map[y + 1] && map[y + 1][x] == '1'
			&& !draw_board(map, x + 1, y, DOWN)))
			return (CUB_OK);
	}
	if (direction == LEFT)
	{
		if ((map[y + 1] && map[y + 1][x] == '1'
			&& !draw_board(map, x, y - 1, DOWN))
			|| (x > 0 && map[y][x - 1] == '1'
			&& !draw_board(map, x + 1, y, LEFT))
			|| (y > 0 && map[y - 1] == '1'
			&& !draw_board(map, x, y - 1, UP)))
			return (CUB_OK);
	}
	map[y][x] = '3';
	return (CUB_ERR);
}

int	go_ud_direction(char **map, int x, int y, int direction)
{
	map[y][x] = '2';
	if (direction == DOWN)
	{
		if ((y > 0 && map[y][x + 1] == '1'
			&& !draw_board(map, x + 1, y, RIGHT))
			|| (map[y + 1][x] && map[y + 1][x] == '1'
			&& !draw_board(map, x, y + 1, DOWN))
			|| (x > 0 && map[y][x - 1] == '1'
			&& !draw_board(map, x - 1, y, LEFT)))
			return (CUB_OK);
	}
	if (direction == UP)
	{
		if ((x > 0 && map[y][x - 1] == '1'
			&& !draw_board(map, x - 1, y, LEFT))
			|| (y > 0 && map[y - 1][x] == '1'
			&& !draw_board(map, x, y - 1, UP))
			|| (map[y][x + 1] && map[y][x + 1] == '1'
			&& !draw_board(map, x + 1, y, RIGHT)))
			return (CUB_OK);
	}
	map[y][x] = '3';
	return (CUB_ERR);
}

int	draw_board(char **map, int x, int y, int direction)
{
	if (map[y][x] == 's')
		return (CUB_OK);
	else if (direction == RIGHT || direction == LEFT)
		return (go_rl_direction(map, x, y, direction));
	else
		return (go_ud_direction(map, x, y, direction));
}

int	is_closed(char **map, int end_of_config)
{
	int	j;

	j = -1;
	while (is_space(map[end_of_config][++j]));
	map[end_of_config][j] = 's';
	if (map[end_of_config][j + 1] == '1'
		&& !draw_board(map, j + 1, end_of_config, RIGHT))
		return (CUB_OK);
	else if (map[end_of_config + 1][j]
		&& map[end_of_config + 1][j] == '1'
		&& !draw_board(map, j, end_of_config + 1, DOWN))
		return (CUB_OK);
	return (CUB_ERR);
}

int	map_check_valid_sym(t_config *cfg, int start_map)
{
	int	j;
	int	player_exist;

	player_exist = 0;
	while (start_map)
	{
		j = 0;
		if (is_empty_line(cfg->config_txt[start_map]))
			return (CUB_ERR);
		while (cfg->config_txt[start_map][j]
			&& cfg->config_txt[start_map][j] != '\n')
		{
			if (is_player(cfg->config_txt[start_map][j]))
			{
				if (player_exist)
					return (TOO_MANY_PLAYERS);
				else
					++player_exist;
			}
			else if (!is_map_object(cfg->config_txt[start_map][j]))
				return (UNKNOW_SYM);
			++j;
		}
		++start_map;
	}
	return (CUB_OK);
}

int	parse_map(t_cub *cub, t_config *cfg, int end_of_config)
{
	int	err;

	err = map_check_valid_sym(cfg, end_of_config);
	if (err)
		return (err);
	err = is_closed(cfg->config_txt, end_of_config);
	return (err);
}
