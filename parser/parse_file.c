#include "cub.h"

int	check_config_param(t_cub *cub)
{
	if (!cub->north_texture)
		ft_putendl_fd("cub3d: north texture not found", 2);
	else if (!cub->south_texture)
		ft_putendl_fd("cub3d: south texture not found", 2);
	else if (!cub->west_texture)
		ft_putendl_fd("cub3d: west texture not found", 2);
	else if (!cub->east_texture)
		ft_putendl_fd("cub3d: east texture not found", 2);
	else if (cub->floor_color < 0)
		ft_putendl_fd("cub3d: floor color not found", 2);
	else if (cub->ceilling_color < 0)
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

int	parse_identefer(t_config *config, char *str)
{
	int	i;
	int	index;

	i = 0;
	index = get_identefer_index(str);
	if (index >= NO_INDEX && i <= EA_INDEX)
	{
		i += 2;
		while (is_space(str[i++]));
		if (!str[i])
			return (EMPTY_IDENTIFER);
		if (config->path_to_texture[index])
			return (IDENTIFER_ALREADY_EXIST);
		config->path_to_texture[index] = ft_strdup(&str[i]);
	}
	else if (index >= F_INDEX && index <= C_INDEX)
	{
		i += 1;
		while (is_space(str[i++]));
		if (!str[i])
			return (EMPTY_IDENTIFER);
		config->path_to_texture[index - F_INDEX] = rgb_parse(&str[i]);
	}
	else if (ft_isdigit(str[i]))
		return (END_CONFIG);
	return (UNKNOW_SYM);
}

int	parse_config(t_cub *cub, t_config *config, int *end_of_config)
{
	int	i;
	int	j;

	i = -1;
	while (config->config_txt[++i])
	{
		j = -1;
		while (is_space(config->config_txt[i][++j]));
		if (config->config_txt[i][j])
		{

		}
	}
	
}

int	fill_list(int fd, t_list **list)
{
	int		len;
	char	*line;

	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		++len;
		if (*line == '\n')
			free(line);
		else
			ft_lstadd_back(list, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return (len);
}

int	read_config(char ***config, char *path_to_cfg)
{
	int		fd;
	t_list	*list;
	int		len;

	fd = open(path_to_cfg, O_RDONLY);
	if (fd < 0)
		return (CUB_ERR);
	len = 0;
	list = NULL;
	if (!fill_list(fd, &list))
		return (EMPTY_FILE);
	*config = lst_to_arr(list, len);
	if (!*config || close(fd))
	{
		ft_lstclear(&list, free);
		return (CUB_ERR);
	}
	return (CUB_OK);
}

int	map_parse(t_cub **cub, char *path_to_cfg)
{
	int			end_of_config;
	int			err;
	t_config	config;

	config.config_txt = NULL;
	err = read_config(&config.config_txt, path_to_cfg);
	if (err)
		return (err);
	*cub = (t_cub *)malloc(sizeof(t_cub));
	if (!*cub)
		return (CUB_ERR);
	err = parse_config(cub, &config, &end_of_config);
	if (err)
	{
		free_str_arr(config);
		free(cub);
		return (err);
	}
	err = parse_map(config, end_of_config);
	if (err)
	{
		free_str_arr(config);
		clear_cub(cub);
		return (err);
	}
	return (CUB_OK);
}
