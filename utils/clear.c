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

void	clear_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->imgs && i < 6)
	{
		if (cub->imgs[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->imgs[i].img);
		++i;
	}
	safe_free(cub->imgs);
	if (cub->mlx_ptr)
	{
		ft_log("destroing window...");
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		safe_free(cub->mlx_ptr);
	}
	ft_log("window destroyed");
	free_strarr(cub->map);
	ft_log("map freed");
	safe_free(cub->player);
	free(cub);
}
