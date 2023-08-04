/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_deneme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:33:16 by sutku             #+#    #+#             */
/*   Updated: 2023/08/04 04:26:14 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	mlx_image_t	*image;

	image = (mlx_image_t *)param;
	for (int32_t i = 0; i < image->width; ++i)
	{
		for (int32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(255, 128, 0, 255);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void	put_dot(t_game *game)
{
	int			x;
	int			y;
	float		angle;

	angle = (float)PI / 180 * -1;
	mlx_put_pixel(game->player->img, 20 / 2, 20 / 2, ft_pixel(255, 128, 0, 255));
	while (angle <= (float)PI * 2)
	{
		angle += (float)PI / 180;
		x = 20/ 2 + roundf(3 * cos(angle));
		y = 20 / 2 + roundf(3 * sin(angle));
		mlx_put_pixel(game->player->img, x, y, ft_pixel(255, 128, 0, 255));
		x = 20/ 2 + roundf(2 * cos(angle));
		y = 20 / 2 + roundf(2 * sin(angle));
		mlx_put_pixel(game->player->img, x, y, ft_pixel(255, 128, 0, 255));
		x = 20/ 2 + roundf(cos(angle));
		y = 20 / 2 + roundf(sin(angle));
		mlx_put_pixel(game->player->img, x, y, ft_pixel(255, 128, 0, 255));
	}
}

void ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player->img->instances->y -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player->img->instances->y += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->img->instances->x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		put_dot(game);
		// game->player->angle -= 0.1;
		// if (game->player->angle < 0)
		// 	game->player->angle += 2 * PI;
		// game->player->delta_x = cosf(game->player->angle);
		// game->player->delta_y = sinf(game->player->angle);
		// game->player->x = game->player->x + game->player->delta_x;
		// game->player->y = game->player->y + game->player->delta_y;
		// mlx_put_pixel(game->player->img, game->player->x, game->player->y, ft_pixel(255, 128, 0, 255));
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->img->instances->x += 5;
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
}


int32_t	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_struct(game);

	if (!(game->mlx = mlx_init(800, 800, "cub3D", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game->player->img = mlx_new_image(game->mlx, 20, 20)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->player->img, 300, 300) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	game->player->angle =	0;
	game->player->delta_x = cos(game->player->img->instances->x);
	game->player->delta_y = sin(game->player->img->instances->y);
	game->player->x = 400;
	game->player->y = 400;
	
	// mlx_loop_hook(game->mlx, ft_randomize, game->player->img);
	// ft_randomize(game->player->img);
	mlx_loop_hook(game->mlx, ft_hook, game);

	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
