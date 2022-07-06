#include "cub.h"

static void in_path_error(char *path, int err)
{
	ft_putstr_fd("Error in texture: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == WRONG_FILE_TYPE)
		ft_putendl_fd("wrong file type", STDERR_FILENO);
	else if (err == CANT_CONVERT)
		ft_putendl_fd("can't convert img", STDERR_FILENO);
}

static int	get_img(t_cub *cub, t_config *cfg, int index, int type)
{
	if (type == XPM)
	{
		ft_log("getting image");
		cub->imgs[index].img = mlx_xpm_file_to_image(
			cub->mlx_ptr,
			cfg->path_to_texture[index],
			&cub->imgs[index].width, &cub->imgs[index].height);
		ft_log("image get end");
	}
	/*if (type == PNG)
	{
		cub->imgs[index].img = mlx_png_file_to_image(
			cub->mlx_ptr,
			cfg->path_to_texture[index],
			&cub->imgs[index].width, &cub->imgs[index].height);
	}*/
	if (!cub->imgs[index].img)
		return (TEXTURE_PATH_ERROR);
	cub->imgs[index].addr = mlx_get_data_addr(cub->imgs[index].img,
		&cub->imgs[index].bits_per_pixel,
		&cub->imgs[index].line_length, &cub->imgs[index].endian);
	if (!cub->imgs[index].addr)
		return (TEXTURE_PATH_ERROR);
	return (CUB_OK);
}

int	convert_img(t_cub *cub, t_config *config)
{
	int	err;
	int	f_type;
	int	i;

	ft_log("images convert");
	i = -1;
	while (++i <= EA_INDEX)
	{ 
		ft_log("image converting...");
		if (!check_file_type(config->path_to_texture[i], ".png"))
			f_type = PNG;
		else if (!check_file_type(config->path_to_texture[i], ".xpm"))
			f_type = XPM;
		else
		{
			in_path_error(config->path_to_texture[i], WRONG_FILE_TYPE);
			return (TEXTURE_PATH_ERROR);
		}
		err = get_img(cub, config, i, f_type);
		if (err)
			return (err);
	}
	ft_log("images convert end");
	return (CUB_OK);
}
