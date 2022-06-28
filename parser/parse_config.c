#include "cub.h"

int	parse_settings(t_cub *cub, t_config *config, int *end_of_config)
{
	int	i;
	int	res;

	i = -1;
	while (config->config_txt[++i])
	{
		*end_of_config = i;
		res = parse_identefer(config, config->config_txt[i]);
		if (res == END_CONFIG)
			break ;
		if (res != CUB_OK)
		{
			error_in_line(config->config_txt[i], res);
			return (INVALID_CONFIG_PARAM);
		}
	}
	if (check_config_param(cub) != CUB_OK)
		return (INVALID_CONFIG_PARAM);
	return (convert_img(cub, config));
}

int	parse_config(t_cub **cub, char *path_to_cfg)
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
	err = parse_settings(cub, &config, &end_of_config);
	if (err)
	{
		free_str_arr(config);
		free(cub);
		return (err);
	}
	err = parse_map(cub, &config, end_of_config);
	if (err)
	{
		free_str_arr(config);
		clear_cub(cub);
		return (err);
	}
	return (CUB_OK);
}
