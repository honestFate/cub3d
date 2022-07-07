#include "cub.h"

t_cub	*cub_init()
{
	int		i;
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (cub)
	{
		cub->imgs = malloc(6 * sizeof(t_img));
		if (!cub->imgs)
		{
			free(cub);
			return (NULL);
		}
		i = -1;
		while (++i < 6)
			cub->imgs[i].img = NULL;
		cub->map = NULL;
		cub->player = NULL;
		cub->mlx_ptr = mlx_init();
	}
	return (cub);
}

void	set_map_size(t_cub *cub)
{
	int	i;
	int	j;
	int	max_width;

	max_width = 0;
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
			++j;
		if (j > max_width)
			max_width = j;
		++i;
	}
	cub->map_height = i;
	cub->map_width = max_width;
}

int close_button(void *cub)
{
	clear_cub(cub);
	exit(0);
	return (0);
}

void	redraw_window(t_cub *cub, int index)
{
	(void)index;
	draw_minimap(cub);
	mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->imgs[SCREEN_INDEX].img, 0, 0);
	/*mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->imgs[MINIMAP_INDEX].img, 100, 100);*/
	/*mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->imgs[index].img, 0, 0);*/
}

void	move_player(t_cub *cub, int direction)
{
	float	radian;
	float	x;
	float	y;

	/*if (cub->player->rotate > 360 || cub->player->rotate < 0)
		cub->player->rotate = abs(cub->player->rotate) % 360;*/
	x = 0;
	y = 0;
	radian = cub->player->rotate;
	if (direction == UP)
	{
		x = cub->player->x + 2 * cos(radian);
		y = cub->player->y + 2 * sin(radian);
	}
	else if (direction == DOWN)
	{
		x = cub->player->x - 2 * cos(radian);
		y = cub->player->y - 2 * sin(radian);
	}
	else if (direction == RIGHT)
	{
		x = cub->player->x + 2 * cos(radian + 1.570796);
		y = cub->player->y + 2 * sin(radian + 1.570796);
	}
	else if (direction == LEFT)
	{
		x = cub->player->x + 2 * cos(radian - 1.570796);
		y = cub->player->y + 2 * sin(radian - 1.570796);
	}
	if (cub->map[player_pos(y)][player_pos(x)] != '1')
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

int	key_handler(int key, void *cub)
{
	int	index;

	if (key == 65307) //esc
	{
		clear_cub(cub);
		exit(0);
	}
	if (key == 119) //W
	{
		index = NO_INDEX;
		move_player(cub, index);
		printf("moving forward\n");
	}
	if (key == 97) //A
	{
		index = EA_INDEX;
		move_player(cub, index);
		printf("moving left\n");
	}
	if (key == 115) //S
	{
		index = SO_INDEX;
		move_player(cub, index);
		printf("moving back\n");
	}
	if (key == 100) //D
	{
		index = WE_INDEX;
		move_player(cub, index);
		printf("moving right\n");
	}
	if (key == 65361) //left
	{
		((t_cub *)cub)->player->rotate -= 0.034906;
		printf("watching left\n");
	}
	if (key == 65363) //right
	{
		((t_cub *)cub)->player->rotate += 0.034906;
		printf("watching right\n");
	}
	//printf("%f %f %d\n", ((t_cub *)cub)->player->x, ((t_cub *)cub)->player->y, ((t_cub *)cub)->player->rotate);
	redraw_window(cub, index);
	return (0);
}

int	init_player(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->player = (t_player *)malloc(sizeof(t_player));
	if (!cub->player)
		return (CUB_ERR);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N')
				cub->player->rotate = 4.712388;
			else if (cub->map[i][j] == 'W')
				cub->player->rotate = 3.141592;
			else if (cub->map[i][j] == 'S')
				cub->player->rotate = 1.570796;
			else if (cub->map[i][j] == 'E')
				cub->player->rotate = 0;
			if (is_player(cub->map[i][j]))
			{
				cub->player->x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
				cub->player->y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
				return (CUB_OK);
			}
			++j;
		}
		++i;
	}
	return (CUB_ERR);
}

int	main(int argc, char **argv)
{
	int		err;
	t_cub	*cub;

	err = check_argv(argc, argv);
	if (err)
		return (print_error(err), CUB_ERR);
	cub = cub_init();
	if (!cub)
		return (print_error(err), CUB_ERR);
	err = parse_config(cub, argv[1]);
	if (err)
	{
		ft_log("parse failed");
		clear_cub(cub);
		return (print_error(err), CUB_ERR);
	}
	int i = 0;
	while (cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		++i;
	}
	set_map_size(cub);
	printf("map width - %d\nmap height - %d\n", cub->map_width, cub->map_height);
	init_image(cub, SCREEN_INDEX, 1980, 1080);
	init_image(cub, MINIMAP_INDEX, cub->map_width * BLOCK_SIZE,
		cub->map_height * BLOCK_SIZE);
	ft_log("init finish");
	if (init_player(cub))
	{
		clear_cub(cub);
		return (print_error(CUB_ERR), CUB_ERR);
	}
	mlx_do_key_autorepeaton(cub->mlx_ptr);
	//clear_cub(cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, 1920, 1080, "cub3d");
	ft_log("init finish");
	mlx_hook(cub->win_ptr, 2, 1L<<0, key_handler, cub);
	mlx_hook(cub->win_ptr, 17, 0, close_button, cub);
	mlx_loop(cub->mlx_ptr);
	//start draw
}
