/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:17 by sutku             #+#    #+#             */
/*   Updated: 2023/08/26 01:46:35 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	init_player_direction(t_game *game)
{
	if (game->dir == WE || game->dir == EA)
	{
		if (game->dir == WE)
		{
			game->player->dir_x = -1.0;
			game->player->dir_y = 0.0;
			game->plane_x = 0.0;
			game->plane_y = -0.66;
		}
		else
		{
			game->player->dir_x = 1.0;
			game->player->dir_y = 0.0;
			game->plane_x = 0.0;
			game->plane_y = 0.66;
		}
	}
	if (game->dir == NO || game->dir == SO)
	{
		if (game->dir == NO)
		{
			game->player->dir_x = 0.0;
			game->player->dir_y = -1.0;
			game->plane_x = 0.66;
			game->plane_y = 0.0;
		}
		else
		{
			game->player->dir_x = 0.0;
			game->player->dir_y = 1.0;
			game->plane_x = -0.66;
			game->plane_y = 0.0;
		}
	}
}



void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
	game->wall.num_texture[NO] = 0;
	game->wall.num_texture[SO] = 0;
	game->wall.num_texture[WE] = 0;
	game->wall.num_texture[EA] = 0;
	game->map.map = NULL;
	game->f = 0;
	game->c = 0;
	game->dir = -1;
}

void	player_position(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E' || game->map.map[y][x] == 'S' || game->map.map[y][x] == 'W')
			{
				game->player->x = (double)x;
				game->player->y = (double)y;
				return ;
			}
		}
	}
	printf(" height %d width %d\n", game->map.height, game->map.width);
}

void	draw_map(t_game *game)
{
	int		i;
	double	camera_x;
	t_coord	distance;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
		game->ray.x = game->player->dir_x + game->plane_x * camera_x;
		game->ray.y = game->player->dir_y + game->plane_y * camera_x;
		if (game->ray.x == 0)
			game->ray.delta_x = 1e30;
		else
			game->ray.delta_x = fabs(1 / game->ray.x);
		if (game->ray.y == 0)
			game->ray.delta_y = 1e30;
		else
			game->ray.delta_y = fabs(1 / game->ray.y);
		distance = dda(game);
		if (game->wall.side % 2 == 0)
			draw_lineof_texture(game, i, distance.x - game->ray.delta_x);
		else if (game->wall.side % 2 != 0)
			draw_lineof_texture(game, i, distance.y - game->ray.delta_y);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_struct(game);
	if (!(game->mlx = mlx_init(1600, 800, "cub3D", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game->img = mlx_new_image(game->mlx, 1600, 800)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	open_map_file(game, "./map.cub");
	player_position(game);
	init_player_direction(game);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
