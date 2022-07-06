#include "cub.h"

void	init_image(t_cub *cub, int index, int width, int height)
{
	cub->imgs[index].img = mlx_new_image(cub->mlx_ptr, width, height);
	cub->imgs[index].addr = mlx_get_data_addr(cub->imgs[index].img,
		&cub->imgs[index].bits_per_pixel,
		&cub->imgs[index].line_length, &cub->imgs[index].endian);
}

void	put_pixel_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	player_pos(float p)
{
	return ((int)roundf((p - BLOCK_SIZE / 2) / BLOCK_SIZE));
}