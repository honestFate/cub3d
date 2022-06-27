#include "cub.h"

void	safe_free(void *data)
{
	if (data)
		free(data);
}

void	free_strarr(char **strings)
{
	int	i;

	i = 0;
	if (strings)
	{
		while (strings[i])
			free(strings[i++]);
		free(strings);
	}
}

void	free_img(t_cub *cub, t_img *img)
{
	if (img && img->img)
		mlx_destroy_image(cub->mlx_ptr, img->img);
	safe_free(img);
}


void	clear_cub(t_cub *cub)
{
	if (cub->north_texture)
		free_img(cub, cub->north_texture);
	if (cub->south_texture)
		free_img(cub, cub->south_texture);
	if (cub->west_texture)
		free_img(cub, cub->west_texture);
	if (cub->east_texture)
		free_img(cub, cub->east_texture);
	if (cub->current_view)
		free_img(cub, cub->current_view);
	if (cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	free_str_arr(cub->map);
	safe_free(cub);
}
