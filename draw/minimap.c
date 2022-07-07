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

void	draw_line(t_cub *cub, int ray_index, float ray_len, float angl)
{
	int	free_space;
	int	line_height;
	int	y;
	float player_angl = cub->player->rotate;

	ray_len /= 25;
	ray_len *= cos(player_angl - angl);
	if (ray_len < 1)
		ray_len = 1;
	line_height = 1080 / ray_len;
	y = 0;
	free_space = 1080 - line_height;
	while (y < free_space / 2)
	{
		put_pixel_img(&cub->imgs[SCREEN_INDEX], ray_index, y,
			cub->ceilling_color);
		++y;
	}
	while (line_height > 0)
	{
		put_pixel_img(&cub->imgs[SCREEN_INDEX], ray_index, y,
			create_trgb(0, 0, 255, 0));
		--line_height;
		++y;
	}
	while (y <= 1080)
	{
		put_pixel_img(&cub->imgs[SCREEN_INDEX], ray_index, y,
			cub->floor_color);
		++y;
	}
}

int	get_direction(int wall_x, int wall_y, int x, int y)
{
	if (x < wall_x && y == wall_y)
		return (WE_INDEX);
	if (x > wall_x && y == wall_y)
		return (EA_INDEX);
	if (x == wall_x && y < wall_y)
		return (SO_INDEX);
	if (x == wall_x && y > wall_y)
		return (NO_INDEX);
	return (CUB_ERR);
}

void	draw_rays(t_cub *cub)
{
	int		ray_index;
	float	angl;
	//float	radian;
	float	x;
	float	y;
	float	x_start;
	float	y_start;
	float	c;

	angl = cub->player->rotate - 0.785398;
	float	range = cub->player->rotate + 0.785398;
	ray_index = 0;
	while (angl <= range)
	{
		c = 0;
		//printf("rad - %f\n", radian);
		x_start = cub->player->x;
		y_start = cub->player->y;
		while (1)
		{
			x = cub->player->x + c * cos(angl);
			y = cub->player->y + c * sin(angl);
			//printf("%f %f %f %f\n", angl, c, x, y);
			int wall_x = player_pos(x);
			int wall_y = player_pos(y);
			if (cub->map[wall_y][wall_x] == '1')
			{
				while (cub->map[player_pos(y)][player_pos(x)] == '1')
				{
					x = cub->player->x + c * cos(angl);
					y = cub->player->y + c * sin(angl);
					c -= 0.1;
				}
				draw_line(cub, ray_index, sqrtf(powf(x - x_start, 2) + powf(y - y_start, 2)), angl);
				break ;
			}
			//put_pixel_img(&cub->imgs[MINIMAP_INDEX], (int)x, (int)y, create_trgb(0, 255, 0, 0));
			++c;
		}
		++ray_index;
		angl += .000818;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	//int	j;

	i = 0;
	//mlx_destroy_image(cub->mlx_ptr, cub->imgs[MINIMAP_INDEX].img);
	//free(cub->imgs[MINIMAP_INDEX].addr);
	//init_image(cub, MINIMAP_INDEX, cub->map_width * BLOCK_SIZE,
		//cub->map_height * BLOCK_SIZE);
	/*while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_block(&cub->imgs[MINIMAP_INDEX], j, i);
			++j;
		}
		++i;
	}*/
	draw_rays(cub);
}
