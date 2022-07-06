#include "cub.h"

void	draw_block(t_img *img, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	x *= BLOCK_SIZE;
	y *= BLOCK_SIZE;
	while (i < BLOCK_SIZE)
	{
		j = 0;
		while (j < BLOCK_SIZE)
		{
			put_pixel_img(img, x + j, y + i, create_trgb(0, 255, 255, 255));
			++j;
		}
		++i;
	}
}

void	draw_rays(t_cub *cub)
{
	int		angl;
	float	radian;
	float	x;
	float	y;
	float	c;

	angl = cub->player->rotate - 30;
	while (angl <= cub->player->rotate + 30)
	{
		c = 0;
		radian = (angl * M_PI) / 180;
		while (1)
		{
			x = cub->player->x + c * cos(radian);
			y = cub->player->y + c * sin(radian);
			//printf("%f %f %f %f\n", radian, c, x, y);
			if (cub->map[player_pos(y)][player_pos(x)] == '1')
				break ;
			put_pixel_img(&cub->imgs[MINIMAP_INDEX], (int)x, (int)y, create_trgb(0, 255, 0, 0));
			++c;
		}
		angl += 1;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	mlx_destroy_image(cub->mlx_ptr, cub->imgs[MINIMAP_INDEX].img);
	//free(cub->imgs[MINIMAP_INDEX].addr);
	init_image(cub, MINIMAP_INDEX, cub->map_width * BLOCK_SIZE,
		cub->map_height * BLOCK_SIZE);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_block(&cub->imgs[MINIMAP_INDEX], j, i);
			++j;
		}
		++i;
	}
	draw_rays(cub);
}
