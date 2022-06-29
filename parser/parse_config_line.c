#include "cub.h"

int	check_config_param(t_config *cfg)
{
	if (!cfg->path_to_texture[NO_INDEX])
		ft_putendl_fd("cub3d: north texture not found", 2);
	else if (!cfg->path_to_texture[SO_INDEX])
		ft_putendl_fd("cub3d: south texture not found", 2);
	else if (!cfg->path_to_texture[WE_INDEX])
		ft_putendl_fd("cub3d: west texture not found", 2);
	else if (!cfg->path_to_texture[EA_INDEX])
		ft_putendl_fd("cub3d: east texture not found", 2);
	else if (cfg->colors[0] < 0)
		ft_putendl_fd("cub3d: floor color not found", 2);
	else if (cfg->colors[1] < 0)
		ft_putendl_fd("cub3d: ceilling color not found", 2);
	else
		return (CUB_OK);
	return (INVALID_CONFIG_PARAM);
}

int	get_identefer_index(char *str)
{
	if (!ft_strncmp(str, NORTH_TEXTURE_IDENTIFER, 2))
		return (NO_INDEX);
	else if (!ft_strncmp(str, SOUTH_TEXTURE_IDENTIFER, 2))
		return (SO_INDEX);
	else if (!ft_strncmp(str, WEST_TEXTURE_IDENTIFER, 2))
		return (WE_INDEX);
	else if (!ft_strncmp(str, EAST_TEXTURE_IDENTIFER, 2))
		return (EA_INDEX);
	else if (!ft_strncmp(str, FLOOR_COLOR_IDENTIFER, 1))
		return (F_INDEX);
	else if (!ft_strncmp(str, CEILLING_COLOR_IDENTIFER, 1))
		return (C_INDEX);
	return (-1);
}

int	parse_path(t_config *config, char *str, int index)
{
	int	i;

	i = 0;
	while (is_space(str[i++]));
	if (!str[i])
		return (EMPTY_IDENTIFER);
	if (config->path_to_texture[index])
		return (IDENTIFER_ALREADY_EXIST);
	config->path_to_texture[index] = ft_strdup(&str[i]);
	return (CUB_OK);
}

int	parse_color(t_config *config, char *str, int index)
{
	int	i;

	i = 0;
	while (is_space(str[i++]));
	if (!str[i])
		return (EMPTY_IDENTIFER);
	if (parse_rgb(&str[i], config->path_to_texture[index - F_INDEX]))
		return (INVALID_CONFIG_PARAM);
	return (CUB_OK);
}

int	parse_identefer(t_config *config, char *str)
{
	int	i;
	int	index;

	i = 0;
	while (is_space(str[i++]));
	if (!str[i++])
		return (CUB_OK);
	index = get_identefer_index(str);
	if (index >= NO_INDEX && i <= EA_INDEX)
		return (parse_color(config, str + i + 2, index));
	else if (index >= F_INDEX && index <= C_INDEX)
		return (parse_path(config, str + i + 1, index));
	else if (ft_isdigit(str[i]))
		return (END_CONFIG);
	return (UNKNOW_SYM);
}
