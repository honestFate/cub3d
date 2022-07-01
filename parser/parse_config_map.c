#include "cub.h"

int	is_empty_line(char *line)
{
	while (is_space(line++));
	if (!line)
		return (1);
	return (0);
}

int	is_close_line(char *line, int j)
{
	int	len;

	len = ft_strlen(line);
	if (len - 1 > j)
		if (is_inner_object(line[j + 1]))
			return (CUB_ERR);
	if (len - 1 >= j)
		if (is_inner_object(line[j]))
			return (CUB_ERR);
	if (j > 0 && len - 2 >= j)
		if (is_inner_object(line[j - 1]))
			return (CUB_ERR);
	return (CUB_OK);
}

int	is_closed(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if ((i > 0 && is_close_line(map[i - 1], j))
					|| (j > 0 && is_inner_object(map[i][j - 1]))
					|| (map[i][j + 1] && is_inner_object(map[i][j + 1]))
					|| (map[i + 1] && is_close_line(map[i + 1], j)))
					return (UNCLOSED_MAP);
			}
		}
	}
	return (CUB_OK);
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
		while (cfg->config_txt[start_map][j])
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
